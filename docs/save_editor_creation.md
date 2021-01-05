# 如何创建EdiZon存档文件编辑器

## 介绍

EdiZon为开发人员提供了一个统一的界面，以在其中构建存档编辑器，并供用户之后使用。 这使开发人员不必担心为其存档编辑器编写精美的GUI，因此他们可以专注于重要的事情，即存档编辑。 
为此，EdiZon使用了一个配置文件（该文件描述了存档编辑界面应显示的属性）以及一个Lua或Python脚本，该脚本根据用户输入进行编辑。

## 要求

- 任何游戏的存档文件
- 有Lua或Python经验
- 有文件格式以及如何分析未知文件类型相关的知识

## 配置文件

通过一个配置文件让EdiZon知道如何构建其界面。 
配置文件是一个名为 `<titleID>.json` 的JSON格式的文本文件，该文件放置在EdiZon的搜索目录 `/switch/EdiZon/configs` 中。

**典型的配置文件可能如下所示：**

```json
{
    "author" : "WerWolv",
    "description" : "存档编辑器配置示例，用以测试编辑器",
    "scriptLanguage" : "python",
    "beta" : true,
    "all" : [
        {
            "pathRegex" : [ "path", "\\d+", "[a-zA-Z0-9]+_\\d+" ],
            "fileNameRegex" : "filename\\.sav",
            "script" : "test.py",
            "items" : [
                {
                    "name" : "整数值A",
                    "infoText" : "这是一个整数值示例",
                    "category" : "类别1",
                    "arguments" : {
                        "numItems" : 555,
                        "enabled" : true,
                        "item" : "sword",
                        "durability" : 0.125
                    },
                    "widget" : {
                        "type" : "int",
                        "minValue" : 0,
                        "maxValue" : 1000
                    }
                },
                {
                    "name" : "整数值B",
                    "infoText" : "这是第二个整数值示例",
                    "category" : "类别2",
                    "arguments" : {
                        "test" : "Hello World"
                    },
                    "widget" : {
                        "type" : "int",
                        "minValue" : 0,
                        "maxValue" : 1000
                    }
                },
                {
                    "name" : "布尔值",
                    "infoText" : "这是一个布尔值示例",
                    "category" : "类别1",
                    "arguments" : {
                        "derp" : 3.141592654
                    },
                    "widget" : {
                        "type" : "bool",
                        "onValue" : 69,
                        "offValue" : 420
                    }
                },
                {
                    "name" : "字符串值",
                    "infoText" : "这是一个字符串值示例",
                    "category" : "类别1",
                    "arguments" : {
                        "testA" : true,
                        "testB" : false
                    },
                    "widget" : {
                        "type" : "string",
                        "minLength" : 5,
                        "maxLength" : 32
                    }
                },
                {
                    "name" : "注释",
                    "infoText" : "一些注释",
                    "category" : "类别1",
                    "arguments" : {
                        "testA" : true,
                        "testB" : false
                    },
                    "widget" : {
                        "type" : "注释",
                        "comment" : "当试图了解上述值的含义时，这篇冗长而超级详尽的注释将对您有很大帮助。"
                    }
                },
                {
                    "name" : "列表值",
                    "infoText" : "这是一个列表值示例",
                    "category" : "类别1",
                    "arguments" : {
                        "testA" : true,
                        "testB" : false
                    },
                    "widget" : {
                        "type" : "list",
                        "keys" : [ "Value 1", "Value 2", "Value 3", "Value 4"],
                        "values" : [ 555, 1337, 69, 420 ]
                    }
                },
                {
                    "name" : "进度条",
                    "infoText" : "这是一个进度条案例",
                    "category" : "类别3",
                    "arguments" : {
                        "testA" : true,
                        "testB" : false
                    },
                    "widget" : {
                        "type" : "progress"
                    }
                }
            ]
        }
    ]
}
```

### 配置文件元数据

| 键名            | 描述                                                        | 示例值         |
|-----------------|-------------------------------------------------------------|----------------|
| `author`        | 存档文件编辑器的作者。                                          | `WerWolv`      |
| `description`   | 打开存档编辑器菜单时将向用户显示的简短说明。                      | `可以编辑金币、生命值和物品` |
| `beta`          | 是否此存档编辑器已经经过多人测试，每个人都可以安全使用。 | `false` |
| `all` / `X.Y.Z` | 这里的键名可以不同，并且这些键可以有多个不同的名称。如果使用 `X.Y.Z` 格式，则仅当在Switch上安装了此游戏的特定版本时，才会加载配置文件的这一部分。如果使用 `all` 将使配置的这一部分可用于游戏的每个版本。 | `特定版本的配置元数据列表，可用于不同的文件` |

### 版本和文件特定的元数据

在 `配置文件元数据` 中描述的 `all` 或者 `X.Y.Z` 键的值是这些版本和特定于文件的元数据项的列表。该列表的每个条目可以具有不同的配置，因此可以针对存档文件系统中的不同文件。这用于游戏将不同的信息存储在单独的文件中时(例如，库存数据进入stock.bin，玩家数据进入player.bin)。

| 键名             | 描述                                                                                                  | 示例值                                    |
|------------------|------------------------------------------------------------------------------------------------------|-------------------------------------------|
| `pathRegex`      | 字符串列表，每个字符串包含存档文件路径的一部分。这些字符串是正则字符串，因此路径中的每个目录都可以被正则匹配。 | `[ "path", "\\d+", "[a-zA-Z0-9]+_\\d+" ]` |
| `fileNameRegex`  | 正则字符串，用来匹配由EdiZon编辑的存档文件。                                                             | `filename\\.sav`                         |
| `scriptLanguage` | 用于编辑存档文件的脚本语言。                                                                            | `python` 或 `lua`                         |
| `script`         | 用来编辑保存文件的脚本文件名。                                                                          | `json.lua`                                |
| `items`          | 这是将在编辑器界面中显示的配置项目的列表。 每一项将用于编辑保存文件中的一个属性。                            | 参见 `小组件元数据`                        |

### 小组件元数据

窗口小组件是编辑器窗口中的列表项，它们将与脚本进行通信，并最终根据用户的输入来编辑存档文件。

| 键名            | 描述                                   | 示例值                |
|-----------------|---------------------------------------|-----------------------|
| `name`          | 属性名称                               | `币数`                |
| `description`   | 关于此小组件编辑内容的简短描述           | `玩家拥有的金币数量。` |
| `category`      | 该小组件将按类别名排序。                | `收藏品`               |
| `arguments`     | 使用此窗口小组件时，传递给脚本文件的参数  | 参见 `参数`            |
| `widget`        | 小组件依赖元数据                        | 参见 `小组件依赖元数据` |

### 参数

每当用户与窗口小组件交互时，这些键值对将传递到脚本。这些参数用于告诉脚本要修改的地址，要更改的属性或要编辑的值的大小或类型。参数键的名称可以是任何适合脚本需求的字符串。值可以是 `数字`、`浮点数`、`字符串`或`布尔值`。列表、json对象和null将使得参数不会传递到脚本，因此被视为未定义。

**参数对象中的键和值都是用户定义的，可以设置为对脚本有用的任何值**

### 小组件依赖元数据

有多种不同类型的小组件可用于修改数据。可用的类型有：`int`、`bool`、`string`、`list`、`slider`、`progress`和`comment`，它们是`type`值能被设置有效值的类型。其他任何类型都将导致窗口小组件无法加载。根据设置的`type`值，EdiZon将会设置不同的参数。

#### 整形小组件

该小组件，将在选定时打开键盘，并等待用户输入整数。当用户仅关闭键盘并没有修改数据时，不会传递给脚本。

| 键名            | 描述                                                   | 示例值  |
|-----------------|--------------------------------------------------------|--------|
| `minValue`      | 此小组件可以设置的最小值。低于下限的值会限制到 `minValue`。| `0`    |
| `maxValue`      | 此小组件可以设置的最大值。高于上限的值会限制到 `maxValue`。| `9999` |

#### 布尔小组件

具有'开'和'关'状态的窗口小组件，该窗口小组件在选定时切换值。如果脚本获取的值既不是`onValue`也不是`offValue`，那么EdiZon会将其解释为'关'的属性，并在用户下次选择小组件时将其设置为`onValue`。

| 键名            | 描述                        | 示例值 |
|-----------------|----------------------------|--------|
| `onValue`       | 选择开状态时将传递到脚本的值  | `1234` |
| `offValue`      | 选择关状态时将传递到脚本的值  | `1000` |

#### 字符串小组件

该小组件，将在选定时打开键盘，并等待用户输入数字。当用户仅关闭键盘时，不会传递值给脚本。

| 键名            | 描述                                                                                    | 示例值 |
|-----------------|----------------------------------------------------------------------------------------|--------|
| `minLength`     | 此小组件可以设置的字符串的最小长度。如果输入了较短的字符串，则输入将被忽略，并且不会传递给脚本。| `0`    |
| `maxLength`     | 此小组件可以设置的字符串的最大长度。软件键盘将阻止用户输入比此更长的字符串。                  | `32`   |

#### 列表小组件

选择时将显示下拉菜单的小组件。这允许命名无限数量的值，并将它们显示在列表中以呈现给用户。键列表中的每个字符串都将映射到值列表中相同索引处的值，因此键列表和值列表的长度必须相同。值可以是`numbers`、`floats`、`booleans`和`strings`类型，但所有值都应属于对应的类型。

| 键名            | 描述              | 示例值                                          |
|-----------------|------------------|-------------------------------------------------|
| `keys`          | 显示给用户的名称。 | `[ "Value 1", "Value 2", "Value 3", "Value 4"]` |
| `values`        | 传递给脚本的值。   | `[ 555, 1337, 69, 420 ]`                        |

**TODO：摇杆**</br>
**TODO: 进度条**

#### 注释小组件

该小组件，它将在小部件列表中插入一些文本，该文本用于提供编辑器屏幕中任何内容的附加信息。

| 键名            | 描述                        | 示例值                              |
|-----------------|----------------------------|-------------------------------------|
| `comment`       | 将显示的注释文本。           | `在启用此选项之前，请确保教程已完成。` |

## 脚本文件

存档编辑器脚本可以用Lua或Python编写。EdiZon将Lua版本5.3.5和Python 3.8与其完整的标准库打包在一起。如果需要，可以在存档编辑脚本中添加和导入其他库。

### Hello World 脚本

#### Lua

!!! 注意
    `edizon`模块**不是**必须在lua中导入。它是一个自动加载的公开注册的模块，并一致被称为`edizon`。

```lua
-- Load the current save data in as a byte array --
saveFileBuffer = edizon.getDataAsBuffer()

-- Get a value from the save data --
function getValue()
    -- Get the address and size argument from the config file for this widget --
    address = edizon.getArgument("address")
    size = edizon.getArgument("size")
    value = ...
    -- ... use address and size to get the requested value from the save file ... --

    return value
end

-- Set a value in the save data --
function setValue(value)
    -- Get the address and size argument from the config file for this widget --
    address = edizon.getArgument("address")
    size = edizon.getArgument("size")

    -- ... use address and size to set the requested part of the save file to value ... --

    saveFileBuffer[...] = value
end

-- Return the modified save data to EdiZon --
function getModifiedSaveFileData()
    -- Recalculate checksums / fixup save data to be ready for injecting --
    return saveFileBuffer
end
```

#### Python

!!! 注意
    `edizon`模块必须在Python里手动导入。

```python
# Import edizon module
import edizon

# Load the current save data in as a byte array
saveFileBuffer = edizon.getDataAsBuffer()

# Get a value from the save data
def getValue():
    # Get the address and size argument from the config file for this widget
    address = edizon.getArgument("address")
    size = edizon.getArgument("size")

    # ... use address and size to get the requested value from the save file ...

    return value

# Set a value in the save data
def setValue(value):
    # Get the address and size argument from the config file for this widget
    address = edizon.getArgument("address")
    size = edizon.getArgument("size")

    # ... use address and size to set the requested part of the save file to value ...
    saveFileBuffer[...] = value

# Return the modified save data to EdiZon
def getModifiedSaveFileData():
    # Recalculate checksums / fixup save data to be ready for injecting
    return saveFileBuffer
```

### _**EdiZon调用的函数**_

#### `全局空间`

EdiZon在脚本中调用任何函数之前，将执行全局空间中的代码。在这里应该进行悄无声息的存档文件解析，因为全局空间在启动时只会执行一次。

!!! 警告
    请**不要**在`getValue`或`setValue`函数中解析整个存档数据！每当用户与编辑器界面交互时，这些函数就会执行。每当发生这种情况时，解析存档的数据都会拖慢接口，因此不应该这样做。

#### `getValue( ) -> int | float | boolean | string`

当EdiZon想要在编辑器界面中显示属性的当前值时，将调用此函数。它应该从配置文件中加载当前参数，并使用它们从存档数据中加载正确的值。然后通过函数的(`返回值`)将其传递给EdiZon。该值可以是`int`、`float`、`boolean`或`string`类型，具体取决于配置文件和所使用的小组件。

#### `setValue( int | float | boolean | string )`

当用户与任何窗口小组件交互时，将调用此函数，因此存档数据中的值会被更新。该值将作为函数的第一个也是唯一的参数传入，并且可以是`int`、`float`、`boolean`或`string`类型，具体取决于配置文件和所使用的小组件。

#### `getModifiedSaveFileData( ) -> byte[]`

用户确认所修改的数据后，并在界面中点击`应用`后，就会立即调用此函数。它会对解析后的存档数据进行重新编码，可能会重新计算校验和，并为游戏重新读取存档数据做任何必要的事情。一旦完成，它会将数据从函数返回给EdiZon(`return saveDataBuffer`)。此函数只能返回字节数组。

### _**脚本可调用的EdiZon函数**_

#### `edizon.getDataAsBuffer( ) -> byte[]`

此函数将当前加载的存档数据作为字节数组返回。对于二进制存档格式很有用。

#### `edizon.getDataAsString( ) -> string`

此函数以字符串形式返回当前加载的存档数据。对于纯文本保存格式很有用。

#### `edizon.getArgument( string ) -> int | float | boolean | string`

每次用户与窗口小组件进行交互时，EdiZon都会从配置中加载该窗口小组件的参数，并将其传递给脚本引擎。然后，可以使用此函数基于它们的名称访问这些参数值。这样，脚本可以知道应编辑哪些值并做出相应的反应。
