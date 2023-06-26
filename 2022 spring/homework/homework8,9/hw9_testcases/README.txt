main.cpp中包含各测试点的内容。
为了测试，我们对ProvidedFramework中部分代码做了微小的修改。

本地运行测试的方法：

1. 将你提交的部分与测试部分组合在一起：将你src/下的，不包括ProvidedFramework、main.cpp
在内的文件复制到这里的src/下相同位置，并把CMakeLists.txt也复制到这里。

2. 在本目录下python运行modify_cmakelists_local.py。
此脚本会剔除你的CMakeLists里对图形化界面的依赖。 运行后，CMakeLists内容应不含freeglut。

3. 新建build文件夹，并和你第一次打开项目时一样，从头开始构建一个新的CMake项目。
具体步骤与作业描述pdf末尾的部分相同，一样需要设置启动项等步骤。

4. 默认运行会从头到尾进行所有测试点的测试。若运行很慢，可以将project选项从Debug更改为Release
（也可在命令行运行CMake时加入-DCMAKE_BUILD_TYPE=Release选项）
将main.cpp第14行的#define TEST_ALL注释掉即可运行单个case测试，运行时控制台输入case编号。