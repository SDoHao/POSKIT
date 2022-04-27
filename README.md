# POSKIT
It is convenient to fix atoms in poscar files.\n
windows运行exe文件\n
Linux 在命令行用./poskit运行文件\n

如果在linux下运行遇到Permission denied\n
用chmod 777 poskit修改权限 \n

linux下编译 gcc main.c file.c cmd.c trim.c -o poskit\n

指令\n
load         l 读取文件\n
    l pos/POSCAR  按路径pos/POSCAR读取文件 ./pos/POSCAR\n
    l ../pos/POSCAR  ../上层文件夹下的pos/POSCAR\n
save         s 保存POSCAR文件\n
	s-n 以POSCAR_new为名保存文件\n
	s-f 覆盖原文件保存\n
	s aaa 以aaa为名保存文件\n
print        p 输出显示\n
unfix        u 取消固定原子\n
fix            f 固定原子\n
    f-e C H 	将所有C H原子固定\n
    f-l 1 40 	将序号1到40的原子固定\n
    f-l -10		将倒数10行的原子固定\n
    f-h 0.01 0.02 	将z轴范围在0.01到0.02的原子固定\n
pwd         输出当前打开的文件路径\n
pte	输出元素周期表\n
exit	e 退出程序\n

不要输入中文\n
