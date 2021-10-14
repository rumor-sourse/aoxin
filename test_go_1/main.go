//我在完成第一题的基础上增加了一些小功能，使单纯的注册不显得那么苍白
package main

import (
	"errors"
	"fmt"
	"net/http"
	"github.com/gin-gonic/gin"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)
var (
	DB *gorm.DB
)
//Todo model
type Todo struct {
	ID     int    `json:"id"`
	Title  string `json:"title"`
	Status bool   `json:"status"`
}
type Yonghu struct {
	ID 		int    `json:"id"`
	Yonghuming string  `json:"name"`
	Mima  		string  `json:"pass"`
}
func initMySQL() (err error) {
	dsn := "root:wszjdfs123456@tcp(localhost:3306)/db1?charset=utf8mb4&parseTime=True&loc=Local"
	DB, err = gorm.Open("mysql", dsn)
	if err != nil {
		return
	}
	return DB.DB().Ping()
}
func main(){
    //创建数据库
	//create database db1;
	//连接数据库
	err := initMySQL()
    if err != nil {
		panic(err)
	}
	defer DB.Close() //程序退出关闭数据库
	//模型绑定
	DB.AutoMigrate(&Todo{}) //todos
	DB.AutoMigrate(&Yonghu{})  //yonghus
    r := gin.Default()
	//加载静态文件
	r.StaticFS("/static", http.Dir("./static"))
	r.LoadHTMLFiles("./login.html","./index.html","./register.html","./login_err.html")
	r.GET("/login",func(c *gin.Context){
		c.HTML(http.StatusOK,"login.html",nil)
	})
    r.GET("/register",func(c *gin.Context){
		c.HTML(http.StatusOK,"register.html",nil)
	})
    r.POST("/register",func(c *gin.Context){
        name := c.PostForm("name")
        pass := c.PostForm("pass")
		fmt.Print(name+"\n"+pass)
		yonghu := Yonghu{Yonghuming:name,Mima:pass}
		if err = DB.Create(&yonghu).Error; err != nil {
			c.JSON(http.StatusOK, gin.H{"error": err.Error()})
		} else {
			c.Request.URL.Path = "/login"
			r.HandleContext(c)
		}
    })
	r.GET("/login_err",func(c *gin.Context){
		c.HTML(http.StatusOK,"login_err.html",nil)
	})
	r.POST("/login_err",func(c *gin.Context){
		c.HTML(http.StatusOK,"login_err.html",nil)
	})
    r.POST("/login",func(c *gin.Context){
        name := c.PostForm("name")
        pass := c.PostForm("pass")
		var yonghu Yonghu	
		err := DB.Debug().First(&yonghu,"yonghuming=? AND mima=?",name,pass).Error
		fmt.Print(err)
		fmt.Print("\n")
		if errors.Is(err, gorm.ErrRecordNotFound) {
			c.Request.URL.Path = "/login_err"
			r.HandleContext(c)
		} else {
			c.HTML(http.StatusOK,"index.html",gin.H{
				"Name":name,
				"Pass":pass,
			})
		//v1
		v1Group := r.Group("v1")
		{
			//待办事项
			//添加
			v1Group.POST("/todo", func(c *gin.Context) {
			//前端页面填写待办事项 点击提交
			//1、从请求中把数据拿出来
			var todo Todo
			c.BindJSON(&todo)
			//2、存入数据库
			//3、返回响应
			if err = DB.Create(&todo).Error; err != nil {
				c.JSON(http.StatusOK, gin.H{"error": err.Error()})
			} else {
				c.JSON(http.StatusOK, todo)
			}
		})
		//查看所有待办事项
		v1Group.GET("/todo", func(c *gin.Context) {
			//查询todo这个表里所有数据
			var todolist []Todo
			if err = DB.Find(&todolist).Error; err!= nil {
				c.JSON(http.StatusOK,gin.H{"error": err.Error()})
			}else {
				c.JSON(http.StatusOK,todolist)
			}
		})
		// 查看某一个待办事项
		// v1Group.GET("/todo/:id", func(c *gin.Context) {

		// })
		//修改某一个待办事项
		v1Group.PUT("/todo/:id", func(c *gin.Context) {
			id,ok := c.Params.Get("id")
			if !ok{
				c.JSON(http.StatusOK,gin.H{"error": "无效的id"})
				return
			}
			var todo Todo
			if err = DB.Where("id=?",id).First(&todo).Error; err!=nil{
				c.JSON(http.StatusOK,gin.H{"error": err.Error()})
				return 
			}
			c.BindJSON(&todo)
			if err = DB.Save(&todo).Error; err!= nil{
				c.JSON(http.StatusOK,gin.H{"error":err.Error()})
			}else{
				c.JSON(http.StatusOK,todo)
			}
		})
		//删除某一个待办事项
		v1Group.DELETE("/todo/:id", func(c *gin.Context) {
			id,ok := c.Params.Get("id")
			if !ok{
				c.JSON(http.StatusOK,gin.H{"error": "无效的id"})
				return
			}
			if err = DB.Where("id=?", id).Delete(Todo{}).Error;err!=nil{
				c.JSON(http.StatusOK,gin.H{"error":err.Error()})
			}else{
				c.JSON(http.StatusOK,gin.H{id:"deleted"})
			}
		})

	}
		}
    })
    r.Run(":8080")
}