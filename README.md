# ChatServer
可以工作在nginx tcp负载均衡中的集群聊天服务器和客户端，基于muduo库实现的，使用了redis服务器
## 项目结构
Project：
        bin/                 --存放可执行文件
        lib/                 --存放库文件
        include/             --存放头文件
        src/                 --存放源文件
        build/               --存放编译文件
        example/
        thirdparty/
        CMakeList.txt
        autobuild.sh
        ReadME.md
        
创建数据库表的mysql代码：
-- 用户表
```mysql
DROP TABLE IF EXISTS `User`;
CREATE TABLE `User` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(50) NOT NULL UNIQUE,
  `password` VARCHAR(50) NOT NULL,
  `state` ENUM('online', 'offline') NOT NULL DEFAULT 'offline',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

-- 好友表（双向关系可各插一条）
DROP TABLE IF EXISTS `Friend`;
CREATE TABLE `Friend` (
  `userid` INT NOT NULL,
  `friendid` INT NOT NULL,
  PRIMARY KEY (`userid`, `friendid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 组表
DROP TABLE IF EXISTS `AllGroup`;
CREATE TABLE `AllGroup` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `groupname` VARCHAR(50) NOT NULL UNIQUE,
  `groupdesc` VARCHAR(200) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 组用户关联表
DROP TABLE IF EXISTS `GroupUser`;
CREATE TABLE `GroupUser` (
  `groupid` INT NOT NULL,
  `userid` INT NOT NULL,
  `grouprole` ENUM('creator', 'normal') NOT NULL DEFAULT 'normal',
  PRIMARY KEY (`groupid`, `userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 离线消息表
DROP TABLE IF EXISTS `OfflineMessage`;
CREATE TABLE `OfflineMessage` (
  `userid` INT NOT NULL,
  `message` VARCHAR(500) NOT NULL -- 存 JSON 字符串
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;



测试json用例     张三登录消息{"msgid":1,"id":1,"password":"123456"} 
                 李四注册消息{"msgid":3,"name":"li si","password":"666666"}
                 李四登录消息{"msgid":1,"id":2,"password":"666666"}
                 一对一聊天消息{"msgid":5,"id":1,"from":"zhang san","to":2,"msg":"hello2"}  --zhang san ->li si
                              {"msgid":5,"id":2,"from":"li si","to":1,"msg":"你好"}       --li si-> zhang san
                张三添加好友{"msgid":6,"id":1,"friendid":2}
