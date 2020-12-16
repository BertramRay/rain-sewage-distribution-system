# rain sewage distribution system
 + 这是一款基于TDS传感器，浊度传感器，pH传感器，DC12V三通阀和Arduino UNO开发板的综合雨污分流检测系统。
 + 该项目由清华大学生物医学检测原理与传感技术课程小组共同参与开发，作者：雷梓阳，李子涵，张宇翔，李梓瑜。
 + 该项目文档编写初衷在于利用课程机制对项目进行增量迭代开发。我们认为，两周时间过于短暂，如果进行多次迭代，可以做出更好的作品。
 + 该项目遵循GPL3.0协议。 
 + ![实物图](https://github.com/BertramRay/TsingDetect/blob/main/%E5%AE%9E%E7%89%A9%E5%9B%BE.jpg?raw=true)
## 快速上手
 如果你想基于此项目进行进一步开发，请先确保你具有如下条件。遇到问题请通过邮箱1034495527@qq.com与我取得联系。
### 硬件准备
 1. [Arduino UNO](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.5a472e8d88lSyI&id=584296186027&_u=t2dv10j1b0b7)
 2. [pH传感器套装](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.4c062e8dGbqGEK&id=597437202916&_u=g2dv10j1c1ba)
 3. [浊度传感器套装](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.4c062e8dGbqGEK&id=597601686161&_u=g2dv10j1adda)
 4. [TDS传感器套装](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.4c062e8dGbqGEK&id=598004271714&_u=g2dv10j10cbe)
 5. [杜邦线公对公，母对母，公对母10cm各40pin](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.5a472e8d88lSyI&id=558182761958&_u=t2dv10j18823)
 6. [DC5V转12V模块](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.4c062e8dGbqGEK&id=522572317589&_u=g2dv10j1aea1)
 7. 面包板(实验室有)
 8. [DC12V三通阀](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.4c062e8dGbqGEK&id=620444504991&_u=g2dv10j1f45c)
 9. [TDS标准校正液1382ppm](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.4c062e8dGbqGEK&id=597581782781&_u=g2dv10j16498)
 10. 三通阀对应软管(链接暂无)
### 软件准备
 1. [Arduino uno IDE](https://www.arduino.cc/)
 2. C语言基础，以及对嵌入式硬件开发一定的了解，利用下面题目自测。
  + 我了解arduino setup(),loop()函数
  + 我听说过IIC协议
  + 如果不知道1，我起码接触过其他单片机
### 阅读材料
 1. 详细阅读该项目目前的报告，说明书，pre以及rain_sewage_distribution_system.ino的代码，建立对项目的整体认识。
 2. 粗略阅读各模块PDF资料，理解其工作原理。
### 组装硬件
 1. 根据代码与实物图在面包板上进行连线，请确保完全理解各模块引脚后开始连线。
 2. 组装前建议提前测通并校准各模块
## 开发建议
 如果你对此项目后续的开发方向没有很好的改进思路，这里推荐以下几点
 1. 引入温度传感器，各模块测定准确度对温度均有较高要求，一般是25度左右，在温度不为25度时应外接DS18B12进行温度补偿。
 2. 加入水泵使该系统能够真正做到驱动水流，目前只能使用重力引导水流。
 3. 了解国标实际雨污分流标准，将该标准引入，并修改程序中实际三通阀的参数。
