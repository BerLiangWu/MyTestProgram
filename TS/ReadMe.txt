1.本工具四种混淆模式中仅支持单选，多次膨胀
2.在第一次混淆过后，会创建一个叫Copy.asm的文件，如果处于多次混淆中，会随着混淆次数创建文件
如： 勾选四则运算膨胀  输入膨胀次数为3次，则执行完毕后，会有Copy,2,3三个asm文件，3则为最后一次混淆文件

3.如果需要对已经进行过一次混淆的Copy文件进行其他模式的混淆，请手动更改目标文件，如Copy改为Copy1然后再打开工具进行混淆
4.本工具输出目录为工具所在路径