# 依赖
## 外部依赖
编译前需要安装以下库在电脑中
1. openssl
2. Qt5

设置`src\CMakeLists.txt`相关路径
确保Cmake能找到

## 已集成依赖
httplib
[jison](https://github.com/nlohmann/json)

# 编译
编译工具
vs2017
cmake 3+

```
mkdir build
cmake ..
cmake --build .
```


