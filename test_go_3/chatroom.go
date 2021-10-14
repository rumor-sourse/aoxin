//这个第三题只有私聊功能没实现，虽然但是，我感觉我想的实现私聊的功能挺对的，但是就是不知道为啥不行
//另外为了美观方便，在原要求的基础上还增加了修改名字以及查看所有用户的功能
package main

import (
	"fmt"
	"net"
	"strings"
)

//创建用户结构体类型
type Client struct{
	C chan string
	Name string 
	Addr string
}

//创建全局map，存储在线用户
var onlineMap map[string]Client

//创建全局channel传递用户消息
var message = make(chan string)
//私聊对象和私聊信息
// var privateName = make(chan string)
// var privateMessage = make(chan string)

func WriteMsgToClient(clnt Client, conn net.Conn ){
	//监听用户自带channel上是否有消息
	for msg := range clnt.C{
		conn.Write([]byte(msg + "\n"))
	}
}

func MakeMsg(clnt Client,msg string)(buf string){
	buf =  "["+ clnt.Addr +"]" + clnt.Name +": "+ msg
	return buf
}
func HandlerConnect(conn net.Conn){
	defer conn.Close()
	//获取用户网络地址 ip+port
	netAddr := conn.RemoteAddr().String()
	//创建新连接用户的结构体信息，默认用户是IP+port
	clnt := Client{make(chan string),netAddr,netAddr}
	//将新连接用户，添加到在线用户map中，key:IP+port value:client
	onlineMap[netAddr] = clnt

	//创建专门用来给当前用户发送消息的go程
	go WriteMsgToClient(clnt,conn)

	//发送用户上线消息到全局channel中
	//message <- "["+netAddr +"]" + clnt.Name + "login"
	message <- MakeMsg(clnt,"login")
	//创建一个channel，用来判断退出状态
	isQuit := make(chan bool)

	//创建一个匿名 go 程，专门处理用户发送的消息
	go func(){
		buf := make([]byte,4096)
		for {
			n,err := conn.Read(buf)
			if n == 0 {
				isQuit <- true
				fmt.Printf("检测到客户端:%s退出\n",clnt.Name)
				return 
			}
			if err != nil{
				fmt.Println("conn.Read err:",err)
				return 
			}
			//将读到的用户消息，保存到msg中，string类型
			msg := string(buf[:n-1])
			// 提取在线用户列表
			if msg == "who" && len(msg)== 3{
				conn.Write([]byte("online user list:\n"))
				//遍历当前map ，获取在线用户
				for _,user := range onlineMap{
					userInfo := user.Addr + ":" +user.Name + "\n"
					conn.Write([]byte(userInfo))
				}
				//判断用户发送了改名命令
			}else if len(msg) >= 8 && msg[:6] == "rename"{			//rename|...
				newName := strings.Split(msg,"|")[1]      //msg[8:]
				clnt.Name = newName        //修改结构体成员name
				onlineMap[netAddr] = clnt     //更新 online
				conn.Write([]byte("rename successful\n"))
			// }else if len(msg) >=15 && msg[:11] == "privatechat" {      //privatechat|...|...
			// 	privateName <-  strings.Split(msg,"|")[1]
			// 	privateMessage <- MakeMsg(clnt,strings.Split(msg,"|")[2])			 
			}else {
			//将读到的用户消息，写入到message中
			message <- MakeMsg(clnt,msg)
			}
		}
	}()

	//保证不退出
	for {
		//监听channel上的数据流动
		select {
			case <- isQuit:
				delete(onlineMap,clnt.Addr)   //将用户从online移除
				message <- MakeMsg(clnt,"logout") //写入用户退出消息到全局channel
				return 
			}
	}
}
func Manager(){
	//初始化 onlineMap
	onlineMap = make(map[string]Client)
	//监听全局channel中是否有数据，有数据存储至msg，无数据阻塞
	for{
	msg := <-message 
	// //实现私聊功能
	// if primsg,ok := <-privateMessage;ok{
	// priname := <-privateName
	// for _,clnt :=range onlineMap{
	//  	if clnt.Name == priname{
	//  		clnt.C <- primsg
	//  		break
	//  	}
	//  }
	// }
	//循环发送消息给所有在线用户
	for _,clnt :=range onlineMap{
		clnt.C <- msg
	}
	}
}
func main(){
	//创建监听套接字
	listener,err :=net.Listen("tcp","localhost:8080")
	if err != nil{
		fmt.Println("Listen err",err)
		return 
	}
	defer listener.Close()
	//创建管理者go程，管理map和全局channel
	go Manager()
	//循环监听客户端连接请求
	for{
		conn,err := listener.Accept()
		if err!= nil{
			fmt.Println("Accept err",err)
			return
		}
		//启动go程处理客户端数据请求
		go HandlerConnect(conn)
	}
}