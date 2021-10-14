package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)
var (
	DB *gorm.DB
)
type Student struct{
	Name string
	Age int
	Score int 
}
func initMySQL() (err error) {
	dsn := "root:wszjdfs123456@tcp(localhost:3306)/test?charset=utf8mb4&parseTime=True&loc=Local"
	DB, err = gorm.Open("mysql", dsn)
	if err != nil {
		return
	}
	return DB.DB().Ping()
}
func main(){
	// create database test;
	err := initMySQL()
    if err != nil {
		panic(err)
	}
	defer DB.Close() //程序退出关闭数据库
	DB.AutoMigrate(&Student{})
	//实现CRUD操作
	//添加
	student1 := Student{Name:"zhangsan",Age:18,Score:96  }
	student2 := Student{Name:"lisi",Age:28,Score:97}
	student3 := Student{Name:"wangwu",Age:38,Score:97}
	DB.Create(&student1)
	DB.Create(&student2)
	DB.Create(&student3)
	//查询
	var student Student
	DB.Debug().Find(&student,"name <> ?","lisi")
	//更新
	DB.Model(&student).Where("name = ?","wangwu").Update("name","wangliu")
	//删除
	DB.Where("name = ?","zhangsan").Delete(&student)
}