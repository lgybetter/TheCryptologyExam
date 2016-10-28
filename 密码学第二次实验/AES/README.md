# 文件加密算法实现

## 一.安装运行

### 1.由于该程序运行的源码是纯c，所以要把c封装成python可调用的包时需要操作系统拥有python-dev包（ubuntu系统为例）或者python-devel包(centOS系统为例)

	sudo apt-get install python-dev

	sudo yum install python-devel


### 2.安装python-dev（python-devel）包的目的主要是为了对c进行python对象和变量的类型转化


### 3.接着就直接在终端中运行make指令


## 二.python封装包的调用方法

### 1.该包封装了一个c函数int makeFIPS（char *, char *, int, int) 对应到python中调用的函数为example.makeFIPS(outputStr, inputStr, keyLen, type), inputStr表示读取文件的路径，outputStr表示输出文件的路径，keyLen表示密钥的长度（128,192,256)，type表示加解密的类型(1:加密，!1:解密)

### 2.返回的类型是加密中需要填充字符的字节数

### 3.加解密示例:

(1)加密:

	import example
		#从ct.txt中读取明文，输出密文到ct.txt中
		print example.makeFIPS("pt.txt","ct.txt",192,1)
(2)解密:

	import example
		#从ct.txt中读取密文，输出明文到pt2.txt中
		print example.makeFIPS("ct.txt","pt2.txt",192,2)
	


	
