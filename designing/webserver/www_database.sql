drop database if exists www;
create database www;
use www;

create table civ(
username varchar(20) not null,
password varchar(20) not null,
name varchar(20) not null,
telephone varchar(10) not null,
x double not null ,
y double not null,
primary key(username),
index i_n (name),
index i_t (telephone)
);

create table admin(
username varchar(20) not null,
password varchar(20) not null,
primary key(username)
);

create table rescuer(
username varchar(20) not null,
password varchar(20) not null,
car_name varchar(20) not null,
x double,
y double,
time timestamp default current_timestamp,
primary key(username),
index cn(car_name)
);

create table item(
id int not null auto_increment,
name varchar(20) not null,
quantity int not null,
primary key(id),
index i_n (name)
);


create table request(
id int not null auto_increment,
c_name varchar(20) not null,
c_tel varchar(10) not null,
reg_date  timestamp not null default current_timestamp,
i_name varchar(20) not null,
req_quantity int not null,
w_date date,
o_name varchar(20),
primary key(id),
constraint r1 foreign key(c_name) references civ(username) on delete cascade on update cascade,
constraint r2 foreign key(c_tel) references civ(telephone) on delete cascade on update cascade,
constraint r3 foreign key(i_name) references item(name) on delete cascade on update cascade,
constraint r4 foreign key(o_name) references rescuer(car_name) on delete cascade on update cascade
);

create table offering(
id int not null auto_increment,
c_name varchar(20) not null,
c_tel varchar(10) not null,
reg_date date not null,
i_name varchar(20) not null,
off_quantity int not null,
w_date date,
o_name varchar(20),
primary key(id),
constraint o1 foreign key(c_name) references civ(username) on delete cascade on update cascade,
constraint o2 foreign key(c_tel) references civ(telephone) on delete cascade on update cascade,
constraint o3 foreign key(i_name) references item(name) on delete cascade on update cascade,
constraint o4 foreign key(o_name) references rescuer(car_name) on delete cascade on update cascade
);
create table task(
id int not null auto_increment,
r_name varchar(20),
r_i int,
o_i int,
primary key(id),
constraint t1 foreign key(r_name) references rescuer(username) on delete cascade on update cascade,
constraint t2 foreign key(r_i) references request(id) on delete cascade on update cascade,
constraint t3 foreign key(o_i) references offering(id) on delete cascade on update cascade
);
create table announcements (
    id INT AUTO_INCREMENT PRIMARY KEY,
    announcement TEXT,
    time timestamp default current_timestamp
);

create table vasi(
x double not null,
y double not null,
time timestamp default current_timestamp
);