# Property Management System

这是四个大学生的课设项目  
把函数声明放在**function.h**文件里面喵  
把用到的头文件放在**header.h**文件里面喵  

旅店初步构想为10层楼，每层20 间，依据生活常识1楼不住人。

初始状态2—4楼为大床房，5—7为双床房，8—10为高级大床房,因此各个房间初始为60间。

房间信息如下所示：

- 数字1  大床房  20平  200元每间  房间号201—220,   301—320， 401—420.

- 数字2  高级大床房  25平  250元每间  房间号801—820， 901—920， 1001—1020.

- 数字3  双床房  20平  200元每间  房间号501—520， 601—620， 701—720.

讨论的大纲如下 按照三个板块完成

### 登录系统

根据输入的账号和密码识别用户类型，再跳转到到客人，前台，管理员三套子系统中 ==> 前端写

将账号和密码和用户类型存在一个文件里，登录时进行读取

### 客人

1. 查询房间的类型和属性

   通过遍历房间类型的链表完成，即struct room组成的链表 ==> A

2. 查询空房间并预约，要求给定**类型**和**日期**，查询这类房间是否为空 ==> B

   该功能需要通过维护一个长数组完成，数组存储在一个文件中，系统启动时将文件读入内存，关闭时将内存中的数据覆写到文件中
  
   客人预约后产生一条预约信息，写在一个文件中

3. 取消自己的预约 ==> C

   在文件中对应的预约信息后面加上特定符号表示改预约已被取消

4. 查询自己的预约信息 ==> C

   遍历预约链表得到

5. 修改自己的密码 ==> A

6. 查询自己的card类型 ==> A

### 前台

1. 查询所有预约信息 ==> C

   主要目的是查询某个客人是否预约，若已预约，则直接办理入住，若未预约，则先查询是否有空房间，在考虑是否入住

2. 分配空房间 ==> B

   在房间链表中每个房间包含一个数据描述该房间是否已入住，找到未入住的空房间并将其分配给客人，同时修改房间的属性

   并写入一条入住信息

3. 修改自己的密码 ==> A

### 管理员

1. 修改房间信息 ==> A

   直接修改链表中的房间信息即可，并将内存中的数据保存到文件里

2. 修改客人类型 ==> A

   修改账户文件中的内容并保存到文件里

3. 查询，统计，排序各种信息

   包括：客人，房间，预约，入住

   这些信息用四个文件储存
    
   客人信息存储在一个数组中，使用id进行索引 ==> A

   房间信息存储在一个链表中 ==> A

   预约信息存储在文件中，只有排序时才读进内存中并进行排序 ==> C
    
   入住信息存储在文件中，只有排序时才读进内存中并进行排序 ==> B

4. 修改前台，客人的密码 ==> A
