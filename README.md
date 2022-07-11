> 开发时间：2020.02 - 2020.04

# 一、快速开始

方案一：

1. 克隆仓库：使用 Git 克隆仓库或直接下载仓库压缩包到您的计算机
2. 打开工程：使用 `Visual Studio 2019` 或其它版本打开 `ams.sln` 文件
3. 运行项目：在 Visual Studio 中使用快捷键 `Ctrl + F5` 即可运行

方案二：

1. 克隆仓库：使用 Git 克隆仓库或直接下载仓库压缩包到您的计算机
1. 解压运行：解压 `RELEASE` 目录下的 `计费管理系统.zip` 文件并点击解压目录中的 `计费管理系统.exe` 文件即可运行

# 二、项目介绍

计费管理系统是一个控制台应用程序，它的主要应用场景是网吧、机房、电子阅览室等。核心功能是实现对基本数据的维护，并对数据进行统计分析。计费管理系统的核心业务是实现通过输入卡号和密码进行上机，同时开始计费，在用户下机时实现对费用的计算结算操作，并通过本地文件操作保存相关信息。

# 三、技术背景
使用 C 语言进行开发，利用 Visual Studio 2019 集成开发环境。计费管理系统是一个 C 语言控制台程序，综合运用 C 语言基础语法知识、函数、数组、指针、结构体、链表、文件操作等技术，将学习到的理论知识运用到实际项目开发的过程中，对理论知识进行巩固并了解企业的项目开发标准流程。

# 四、系统功能
![在这里插入图片描述](https://img-blog.csdnimg.cn/4fe634fe7af3424d8268d5b237a05fa2.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAU3ByaW5nLV8tQmVhcg==,size_18,color_FFFFFF,t_70,g_se,x_16#pic_center)
# 五、项目迭代
| 阶段                       | 描述                                         |
| :------------------------- | :------------------------------------------- |
| 阶段一：基础知识           | 创建项目框架结构，进行界面设计及数据结构设计 |
| 阶段二：结构体、链表及文件 | 分别使用结构体、链表和文件实现卡管理功能     |
| 阶段三：综合应用           | 采用迭代的思想，逐步实现综合系统             |

# 六、功能演示
## 1. 欢迎界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/202105032205338.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

## 2. 添加卡

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503220537470.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

## 3. 查询卡

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503220542127.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

## 4. 上机

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021050322054747.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

## 5. 下机

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503220552296.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

## 6. 退费

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503220556184.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

## 7. 注销卡

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503220602753.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)
## 8. 退出系统

![退出系统](https://img-blog.csdnimg.cn/20210503220609176.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)
