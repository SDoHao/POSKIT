# POSKIT
It is convenient to fix atoms in poscar files.
windows运行exe文件
Linux 在命令行用./poskit运行文件

如果在linux下运行遇到Permission denied
用chmod 777 poskit修改权限 

linux下编译 gcc main.c file.c cmd.c trim.c -o poskit

指令
load         l 读取文件
    l pos/POSCAR  按路径pos/POSCAR读取文件 ./pos/POSCAR
    l ../pos/POSCAR  ../上层文件夹下的pos/POSCAR
save         s 保存POSCAR文件
	s-n 以POSCAR_new为名保存文件
	s-f 覆盖原文件保存
	s aaa 以aaa为名保存文件
print        p 输出显示
unfix        u 取消固定原子
fix            f 固定原子
    f-e C H 	将所有C H原子固定
    f-l 1 40 	将序号1到40的原子固定
    f-l -10		将倒数10行的原子固定
    f-h 0.01 0.02 	将z轴范围在0.01到0.02的原子固定
pwd         输出当前打开的文件路径
pte	输出元素周期表
exit	e 退出程序

不要输入中文
