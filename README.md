# FawLib
C++公共支持库，目前包括编码转换类、字符串处理类、文件类、目录类、注册表类与安装包类。

## 使用说明

### 编码处理类 faw::Encoding

这个类是一个静态类，无需实例化，只在需要时调用静态方法即可。

这个类首先提供了猜测编码功能，可以猜测一串文本是否是ASCII、UTF8、GB18030或UTF16编码。使用方式为：
```
std::string_view _data = "xxx"; // 或者从文件中读取等等...
std::string _encoding = faw::Encoding::guess (_data);
if (_encoding == "utf8" || _encoding == "ascii") {
	// 能够以utf8方式来解析文本数据
} else if (_encoding == "gb18030" || _encoding == "ascii") {
	// 能够以gb18030方式来解析文本数据
} else if (_encoding == "utf16") {
	// 能够以utf16方式来解析文本数据
}
```

另外也能以单独的方式来判断文本数据是否是某个编码：
```
std::string_view _data = "xxx"; // 或者从文件中读取等等...
if (faw::Encoding::is_ascii (_data)) {
	// 能够以ASCII、utf8或GB18030方式来解析文本数据
} else if (faw::Encoding::is_utf8 (_data)) {
	// 能够以utf8方式来解析文本数据
} else if (faw::Encoding::is_gb18030 (_data)) {
	// 能够以gb18030方式来解析文本数据
} else if (faw::Encoding::is_utf16 (_data)) {
	// 能够以utf16方式来解析文本数据
}
```

除了能判断文本数据编码以外，还能判断是否是某种转码方式：
```
std::string_view _data = "xxx"; // 或者从文件中读取等等...
if (faw::Encoding::is_percent_str (_data)) {
	// %23%E5%FA
} else if (faw::Encoding::is_escape_x_str (_data)) {
	// \xBB\xD2\x2A
} else if (faw::Encoding::is_escape_u_str (_data)) {
	// \u6f73\u23BE
} else if (faw::Encoding::is_base64_str (_data)) {
	// Ga7dX83PdQfnua==
}
```

接下来是编码的转换。提供gb18030、utf8、utf16三种编码的完整的互相转换函数，比如：

```
std::wstring _s = faw::Encoding::gb18030_to_utf16 ("test");
```

相应的把xx_to_xx里面的xx替换为相应的编码方式即可。除此之外还提供了T编码类型，这种类型根据编译方式为多字节或unicode编译方式动态确定为gb18030或utf16，相应的在编码方式位置写上T即可。

然后，此类还提供了常用转码格式的转换函数。
```
// %23%E5%FA
// percent/URL 编码转码函数
std::string _encoded = faw::Encoding::percent_str_encode ("测试");
std::string _decoded = faw::Encoding::percent_str_decode (_encoded);

// \xBB\xD2\x2A
// escape_x 编码转码函数
_encoded = faw::Encoding::escape_x_str_encode (_decoded);
_decoded = faw::Encoding::escape_x_str_decode (_encoded);

// \u6f73\u23BE
// escape_u 编码转码函数
_encoded = faw::Encoding::escape_u_str_encode (_decoded);
_decoded = faw::Encoding::escape_u_str_decode (_encoded);

// Ga7dX83PdQfnua==
// Base64 编码转码函数
_encoded = faw::Encoding::base64_encode (_decoded);
_decoded = faw::Encoding::base64_decode (_encoded);
```

### 字符串类 faw::String

这个类是一个及其简洁的字符串处理类，通过集成编码转码方法，使其可以更加方便的用于几乎所有的场合。不过需要注意的是，它内部是通过std::basic_string类实现，因此它是线程不安全的，使用前请注意。这个类内部会维护一个字符串，维护的字符串以多字节或unicode编译方式动态确定为gb18030或utf16。由于这两种不同编码都能参与字符串类的运算，因此使用当前编码类型的字符串来进行计算能发挥出最大性能。比如_T ("")

首先是生成faw::String对象。gb18030字符串和utf16字符串可以直接传入。以下代码中生成的字符串全部完全等价。

其中，多字节编译时，s1、s3、s5、s7效率高，因为构造时不用转码；同理，unicode编译时，s2、s4、s6、s8效率高。

s7、s8只看右边部分。它俩只在C++17上支持，默认在编译时，类型就是faw::String，因此声明类型可以填auto。

s9、s10均为拷贝字符串，当std::basic_string规则为COW时，拷贝0开销，第一次修改时承受拷贝开销；当std::basic_string规则为SSO时，拷贝承受所有开销，第一次修改时不受其他影响。（这一行不懂没关系，跳过就好）
```
faw::String s1 { "abc" };
faw::String s2 { L"abc" };
faw::String s3 ( "abc" );
faw::String s4 ( L"abc" );
faw::String s5 = "abc";
faw::String s6 = L"abc";
faw::String s7 = "abc"_fs;
faw::String s8 = L"abc"_fs;
faw::String s9 (s1);
faw::String s10 (&s1);
```

然后是“等号=”赋值（+=赋值支持类型与=赋值完全相同，在此不列出代码）：
```
faw::String s1 = "abc"_fs;
faw::String s2 = L"abc"_fs;
faw::String s3 = s1;
faw::String s4 = &s1;
faw::String s5 = "abc";
faw::String s6 = L"abc";
faw::String s7 = std::string ("abc");
faw::String s8 = std::wstring (L"abc");
faw::String s9 = std::string_view ("abc");
faw::String s10 = std::wstring_view (L"abc");
```

另外可以这样，完全不考虑编码方式的随意使用：
```
faw::String s = "abc";
s += L"123";
// 此时s值为 _T ("abc123")
```


接下来是+运算符，支持左+、右+，受支持运算类型与=、+=相同，因此不再列出代码。+运算不改变操作数，表达式最终会生成一个新的faw::Sring。

字符串类支持*、*=操作，使用方式和python一样，也就是相同的字符串循环多少次：
```
String s = "a";
s *= 10;
// 此时s值为 _T ("aaaaaaaaaa")
```

然后是字符串比较，gb18030和utf16编码都可以直接比较，受比较字符串的支持类型与+运算符支持类型相同，在此不全部列出。示例如下：
```
// 区分大小写的比较
String s = "abc";
bool b1 = (s == "abc"); // true
bool b2 = (s.is_equal (L"abc")); // true

// 不区分大小写的比较
bool b3 = s.is_equal_nocase ("Abc"); // true
```

然后是迭代器，支持如下函数：begin、end、cbegin、cend、rbegin、rend、crbegin、crend，使用方式与std::basic_string相同。示例：
```
// 以下代码的输出结果为，a、b、c各占一行
// (只有当类实现了begin和end函数，才支持for-range操作)
faw::String s1 = "abc";
for (auto c: s1) {
    std::cout << (char) c << '\n';
}
```

然后是字符串流的处理。这部分比较有意思的地方在于，很容易实现浮点数等的转换。另外规则是，<<、>>指向代表数据流动方向，faw::String对象在数据流运算的左侧、右侧分别代表对字符串最前、最后的操作。其中两个faw::String字符串类型的流运算很容易出现歧义，因此两个这种字符串类型就不能使用流运算符。
```
faw::String s1 = "12abc";
s1 << _T ('d'); // 此时字符串内容为 12abcd
_T ('-') >> s1; // 此时字符串内容为 -12abcd
s1 << "123"; // 此时字符串内容为 -12abcd123
int i = 0;
s1 >> i; // 此时字符串内容为 -12abcd，i内容为123
i << s1; // 此时字符串内容为 abcd，i内容为-12
```

然后是一些零散的函数，部分源于STL，不过删掉了很多几乎没用的重载函数；其他的用法也很像其他高级语言。杂项函数有：
1. 查找函数：find、rfind
2. 生成新字符串函数：trim_left、trim_right、trim、upper、lower、reverse、replace
3. 修改自身字符串函数：trim_left_self、trim_right_self、trim_self、upper_self、lower_self、reverse_self、replace_self
4. 字符串其他基本方法：empty、clear、free、size、operator[]、c_str、str（返回string_t&）、str_view（返回string_view_t）、stra（返回std::string）、strw（返回std::wstring）、match_regex（传入正则就可以返回匹配内容）
5. split（传入分隔符，返回std::vector&lt;faw::String&gt;）
6. 静态函数format，用于生成一个新的faw::String字符串。
