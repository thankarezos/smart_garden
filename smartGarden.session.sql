

DROP TABLE IF EXISTS `sensors`;
create table `sensors` (
    id int not null AUTO_INCREMENT,
    deviceid int not null,
    soil int not null,
    time TIMESTAMP,
    CONSTRAINT PK_id PRIMARY KEY (id)
);

DROP TABLE IF EXISTS `status`;
create table `status` (
    deviceid int not null AUTO_INCREMENT,
    checkinterval int not null,
    time TIMESTAMP,
    CONSTRAINT PK_userid PRIMARY KEY (deviceid)
);
insert into sensors (soil,isWet) values (800,'YES')
insert into sensors (soil,isWet) values (600,'NO')

insert into status (checkinterval) values (1000)
select * from sensors

SELECT checkinterval FROM status where deviceid=1
UPDATE status
SET checkinterval = 60000
WHERE deviceid = 1;

select * from status

SELECT count(*) as count FROM status where deviceid=1