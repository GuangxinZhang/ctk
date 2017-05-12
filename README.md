## 项目简介 ##
- 名称： ctk
- 开发语言：c
- 当前版本：0.0.1
- 项目概述：c语言实现实时读取文本，并发送至kafka topic

--------------------------------------------------------------------------------
## 环境搭建 ##
- 安装log4c1.2.4<br>
./configure  --prefix=/usr/local/lib/log4c/<br>
./make<br>
./make install<br>
将liglog4c.so.3所在目录/usr/local/lib/log4c/lib/添加到文件/etc/ld.so.conf中<br>
执行：ldconfig<br><br>
- 安装 librdkafka-0.9.3<br>
./configure<br>
./make<br>
./make install<br>
将librdkafka.so所在目录/usr/local/lib/加入/etc/ld.so.conf文件中<br>
安装完毕后执行ldconfig<br><br>
- 修改系统hosts 增加kafka 的brokers<br>
- 编译执行程序：<br>
下载项目源码，进入Release目录，执行make all，即可在当前目录下生成 ctk 的可执行文件。<br>
启动程序：修改log4crc文件的logdir日志目录，修改config.ini对应配置，执行 nohup ./ctk &<br><br>

--------------------------------------------------------------------------------
## 使用 ##
- 在Release目录下，修改config.ini 和 log4crc 配置文件的属性
- nohup ./ctk & 启动程序，后台执行
- config.ini log4crc 和 ctk可执行程序必须放在同一目录

--------------------------------------------------------------------------------
## 常见问题 ##
        log4c:
        ./configure  --prefix=/usr/local/lib/log4c/
        make
        make install  
        error while loading shared libraries: liblog4c.so.3: cannot open shared object file: No such file or directory
        vim /etc/ld.so.conf
        添加：/usr/local/lib
        执行：ldconfig
        /lib64/libc.so.6: version GLIBC_2.14 not found (required by ./agent_pcap_v2)
        下载：http://ftp.gnu.org/gnu/glibc/glibc-2.14.tar.gz
        [root@localhost glibc-2.14]# mkdir build
        [root@localhost glibc-2.14]# cd ./build/
        [root@localhost build]# ../conf
        conf/      configure  conform/   
        [root@localhost build]# ../configure --prefix=/opt/glibc-2.14
        [root@localhost build]# make -j4
        [root@localhost build]# make install
        cp -r /etc/ld.so.c* /opt/glibc-2.14/etc/
        ln -sf /opt/glibc-2.14/lib/libc-2.14.so /lib64/libc.so.6
