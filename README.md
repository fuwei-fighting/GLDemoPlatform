# GLDemoPlatform
基于Glitter项目搭建的面向对象OpenGL测试平台。

不需要写多个`main`函数，整个项目基于模板类和模板方法思想搭建。
如果想要实现自己的渲染效果，只需要构造一个`class`，让这个`class`继承`GLApplication`这个类，然后在`main`函数里修改`GLApplication`指针指向的对象即可。

如果要提升更大的自由度，可以把`GLApplication`的`launch`方法改成`virtual function`，让子类重写这个方法。

`Shader`文件可以考虑写在`Shaders`文件夹中，用`ShaderUtils`这个类来处理`.glsl`文件

`OpenGL`相关的依赖（`glfw、glad`等）全都包含在`Vendor`文件夹中，因此不需要格外引入，直接根目录`load cmake`即可。
