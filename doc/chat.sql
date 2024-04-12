drop table if exists user;
create table user (
	id int(11) primary key not null auto_increment,
	name varchar(50) default null,
	password varchar(50) default null,
	state enum('online','offline')
) engine=InnoDB default charset=utf8;

LOCK TABLES `user` WRITE;
INSERT INTO `user` VALUES (13,'zhang san','123456','online'),(15,'li si','666666','offline'),(16,'liu shuo','123456','offline'),(18,'wu yang','123456','offline'),(19,'pi pi','123456','offline'),(21,'gao yang','123456','offline');
UNLOCK TABLES;

drop table if exists friend;
create table friend (
	userid int(11) not null,
	friendid int(11) not null,
	key userid (userid,friendid)
) engine=InnoDB default charset=utf8;

LOCK TABLES `friend` WRITE;
INSERT INTO `friend` VALUES (13,15),(13,21),(21,13),(21,15);
UNLOCK TABLES;

drop table if exists allgroup;
create table allgroup (
	groupid int(11) primary key not null auto_increment,
	groupname varchar(50) character set latin1 not null,	
	groupdesc varchar(200) character set latin1 default '',
	unique key groupname (groupname)
) engine=InnoDB auto_increment=2 default charset=utf8;

LOCK TABLES `allgroup` WRITE;
INSERT INTO `allgroup` VALUES (1,'C++ chat project','start develop a chat project');
UNLOCK TABLES;

drop table if exists groupuser;
create table groupuser (
	groupid int(11) not null,
	userid int(11) not null,
	grouprole enum('creator','normal') character set latin1 default null,
	key groupid (groupid,userid)
) engine=InnoDB default charset=utf8;

LOCK TABLES `groupuser` WRITE;
INSERT INTO `groupuser` VALUES (1,13,'creator'),(1,21,'normal'),(1,19,'normal');
UNLOCK TABLES;

drop table if exists offlinemessage;
create table offlinemessage (
	userid int(11) not null,
	message varchar(500) not null
) engine=InnoDB default charset=latin1;

LOCK TABLES `offlinemessage` WRITE;
INSERT INTO `offlinemessage` VALUES (19,'{\"groupid\":1,\"id\":21,\"msg\":\"hello\",\"msgid\":10,\"name\":\"gao yang\",\"time\":\"2020-02-22 00:43:59\"}'),(19,'{\"groupid\":1,\"id\":21,\"msg\":\"helo!!!\",\"msgid\":10,\"name\":\"gao yang\",\"time\":\"2020-02-22 22:43:21\"}'),(19,'{\"groupid\":1,\"id\":13,\"msg\":\"hahahahaha\",\"msgid\":10,\"name\":\"zhang san\",\"time\":\"2020-02-22 22:59:56\"}'),(19,'{\"groupid\":1,\"id\":13,\"msg\":\"hahahahaha\",\"msgid\":10,\"name\":\"zhang san\",\"time\":\"2020-02-23 17:59:26\"}'),(19,'{\"groupid\":1,\"id\":21,\"msg\":\"wowowowowow\",\"msgid\":10,\"name\":\"gao yang\",\"time\":\"2020-02-23 17:59:34\"}');
UNLOCK TABLES;