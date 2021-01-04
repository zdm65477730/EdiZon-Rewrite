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
| `items`          | 这是将在编辑器界面中显示的配置项目的列表。 每一项将用于编辑保存文件中的一个属性。                            | 参见 `小部件元数据`                        |

### 小部件元数据

Widgets are the list items in the editor window that will communicate with the script and ultimately edit the save file depending on the user's input.

| Key name        | Description | Example values |
|-----------------|-------------|----------------|
| `name`          | The name of the property | `Coin count` |
| `description`   | A small description about what this widget edits | `The amount of golden coins the player has.` |
| `category`     | The name of the category this widget will be sorted in. | `Collectibles` |
| `args`          | Arguments sent to the script file when this widget gets used | See `Arguments` |
| `widget`        | The widget dependant metadata | See `Widget dependant metadata` |

### Arguments

These key-value-pairs will be sent to the script whenever the user interacts with a widget. These can be used to tell the script what address to modify, what property to change or the size or type of the value that will get edited. The names of the argument keys can be any string that fits the script's needs. Values can be `numbers`, `floats`, `strings` or `booleans`. Lists, json objects and null will cause the arguments to not be passed to the script and therefor being treated as undefined.

**Both the keys and the values inside the arguments object are user defined and can be set to whatever is useful for the script.**

### Widget dependent metadata

There are multiple different types of widgets that can be used to modify data. The available types are `int`, `bool`, `string`, `list`, `slider`, `progress` and `comment` which are the only valid values the `type` value can be set to. Any other one will cause the widget to not load. Dependent on the value `type` was set to, EdiZon will expect different parameters to be set.

#### Integer Widget

A widget that will open the keyboard when selected and expects a number to be entered by the user. The script won't be notified when the user just closes the keyboard.

| Key name        | Description | Example values |
|-----------------|-------------|----------------|
| `minValue`      | The minimum value this widget can be set to. Values lower than it will be capped to `minValue`. | `0` |
| `maxValue`      | The maximum value this widget can be set to. Values higher than it will be capped to `maxValue` | `9999` |

#### Boolean Widget

A widget that can have a ON and a OFF state which gets toggled when selected. If the value reported by the script is neither `onValue` nor `offValue`, EdiZon will interpret this as the property being turned off and will set the value to `onValue` the next time the user selects the widget.

| Key name        | Description | Example values |
|-----------------|-------------|----------------|
| `onValue`       | The value that will be sent to the script when the on-state is selected  | `1234` |
| `offValue`      | The value that will be sent to the script when the off-state is selected | `1000` |

#### String Widget

A widget that will open the keyboard when selected and expects a number to be entered by the user. The script won't be notified when the user just closes the keyboard.

| Key name        | Description | Example values |
|-----------------|-------------|----------------|
| `minLength`      | The minimum length of the string this widget can be set to. If a shorter string is entered, the input will be ignored and the script won't get notified. | `0` |
| `maxLength`      | The maximum length of the string this widget can be set to. The software keyboard will prevent the user to enter a string longer than this | `32` |

#### List Widget

A widget that will display a dropdown menu when selected. This allows for naming an unlimited amount of values and displaying them in a list to present to the user. Every string in the keys list will be mapped to the value at the same index in the values list therefor the keys list and the values list have to be the same length. Values can be `numbers`, `floats`, `booleans` and `strings` but they should all be of the same type.

| Key name        | Description | Example values |
|-----------------|-------------|----------------|
| `keys`          | The names displayed to the user. | `[ "Value 1", "Value 2", "Value 3", "Value 4"]` |
| `values`        | The values sent to the script. | `[ 555, 1337, 69, 420 ]` |

**TODO: slider**</br>
**TODO: progressbar**

#### Comment Widget

A widget that will insert some text in the widget list used to give additional information about anything in the editor screen.

| Key name        | Description | Example values |
|-----------------|-------------|----------------|
| `comment`       | The text that will be displayed. | `Make sure that the tutorial has been completed before enabling this option.`  |

## Script Files

Save editor scripts can be either written in Lua or Python. EdiZon bundles Lua version 5.3.5 and Python 3.8 together with the entirety of it's standard library. If needed, extra libraries can be added and imported in the save editing script.

### Hello World script

#### Lua

!!! Note
    The `edizon` module does **not** have to be imported in lua. It's a publicly registered module that will be loaded automatically and will always be called `edizon`.

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

!!! Note
    The `edizon` module does have to be imported manually on Python.

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

### _**Functions called by EdiZon**_

#### `Global space`

Before EdiZon calls any functions in the script, the code in the global space will be executed. This is where potential save file parsing should be done as the global space will only be executed once on startup.

!!! Warning
    Do **not** parse the whole save data in the `getValue` or `setValue` function! These functions will get executed whenever the user interacts with the editor interface. Parsing the save data every time this happens will lag out the interface and should not be done.

#### `getValue( ) -> int | float | boolean | string`

This function gets called when EdiZon wants to display the current value of a property in the editor interface. It should load the current arguments from the config file and use them to load the correct value from the save data. This value then shall be sent to EdiZon by returning it from the function (`return value`). This value can be of type `int`, `float`, `boolean` or `string` dependant on the config file and the widget used.

#### `setValue( int | float | boolean | string )`

This function gets called when the user interacts with any widget and therefor a value in the save data should be updated. This value will be passed in as the first and only argument of the function and can be of type `int`, `float`, `boolean` or `string` dependant on the config file and the widget used.

#### `getModifiedSaveFileData( ) -> byte[]`

This function will get called as soon as the user decides that they are happy with the modifications and hit `Apply` in the interface. It should re-encode the parsed save data, potentially recalculate checksums and do anything necessary for the save data to be readable again by the game. Once this is done it should return the data from the function back to EdiZon (`return saveDataBuffer`). Only byte arrays can be returned from this function.

### _**EdiZon functions callable by the script**_

#### `edizon.getDataAsBuffer( ) -> byte[]`

This function returns the currently loaded save data as a byte array. Useful for binary save formats.

#### `edizon.getDataAsString( ) -> string`

This function returns the currently loaded save data as a string. Useful for plain text save formats.

#### `edizon.getArgument( string ) -> int | float | boolean | string`

Every time the user interacts with a widget, EdiZon loads the arguments of that widget from the config and puts them into the script engine. This function then can be used to access these argument values based on their names. Like this the script can know what value should get edited and react accordingly.
