# InternVL3 NPU
![Alt text](https://github.com/user-attachments/assets/6d297a34-c516-4cb1-be4a-bca471d40fa6)
<br><br>**User**:\<image\>Describe the image.<br><br>
**Answer**: The image depicts an astronaut in a white space suit lounging on the moon's surface with a green bottle of soda in hand. The background features Earth from space and part of a lunar module, suggesting a surreal scene. The setting is dramatic, with the vastness of space surrounding the astronaut and the Moon itself.

------------

## InternVL3 VLM for RK3588 NPU (Rock 5, Orange Pi 5). <br/>
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)<br/><br/>
Paper: [InternVL3: Exploring Advanced Training and Test-Time Recipes for Open-Source Multimodal Models](https://arxiv.org/pdf/2504.10479)<br/><br/>
Hugging face: https://huggingface.co/OpenGVLab/InternVL3-78B

------------

## Introduction

LLMs (Large Language Models) are neural networks trained on large text datasets to understand and generate language.<br>
VLMs (Vision-Language Models) add a visual encoder so the model can process images and text together.<br> 
A combined VLM+LLM system is often referred to as a multimodal model.

These models can be large—hundreds of millions to billions of parameters—which impacts accuracy, memory use, and runtime speed.<br>
On edge devices like the RK3588, available RAM and compute are limited, and even the NPU has strict constraints on supported operations.<br>
Because of this, models typically need to be quantised or simplified to fit.

Performance is usually expressed in tokens (words) per second.<br>
Once converted to RKNN, parts of the model can run on the NPU, improving speed.<br>
Despite these limits, models like InternVL3 run well on the RK3588 because the NPU efficiently accelerates the heavy math, and the vision encoder can be optimised. This makes advanced multimodal AI feasible on small, power-efficient devices.

------------

## Model performance benchmark (FPS)

All models, with C++ examples, can be found on the Q-engineering GitHub.<br><br>
All LLM models are quantized to **w8a8**, while the VLM vision encoders use **fp16**.<br>

| model         | RAM (GB) | llm cold sec<sup>1</sup> | llm warm sec<sup>2</sup> | vlm cold sec<sup>1</sup> | vlm warm sec<sup>2</sup> | Resolution | Tokens/s |
| --------------| :--: | :-----: | :-----: | :--------: | :-----: | :--------:  | :--------: |
| Qwen2         | | 29.1 |   2.5 | 17.1  | 1.7 | 392 x 392 | 12.5 |
| InternVL3-1B  | 1.3 |  6.8 |   1.1 | 7.8    | 0.75 | 448 x 448 | 30 |
| SmolVLM2-2.2B | | 21.2 |   2.6 | 10.5   | 0.9  | 392 x 392 | 11 |
| SmolVLM2-500M | |  4.8 |   0.7 | 2.5    | 0.25 | 392 x 392 | 31 |
| SmolVLM2-256M | |  1.1 |   0.4 | 2.5    | 0.25 | 392 x 392 | 54 |

<sup>1</sup> When an llm/vlm model is loaded for the first time from your disk to RAM or NPU, it is called a cold start.<br>
The duration depends on your OS, I/O transfer rate, and memory mapping.<br><br> 
<sup>2</sup> Subsequent loading (warm start) takes advantage of the already mapped data in RAM. Mostly, only a few pointers need to be restored.<br>

------------

## Dependencies.
To run the application, you have to:
- OpenCV 64-bit installed.
- rkllm library.
- rknn library.
- Optional: Code::Blocks. (```$ sudo apt-get install codeblocks```)

### Installing the dependencies.
Start with the usual 
```
$ sudo apt-get update 
$ sudo apt-get upgrade
$ sudo apt-get install cmake wget curl
```
#### OpenCV
To install OpenCV on your SBC, follow the Raspberry Pi 4 [guide](https://qengineering.eu/install-opencv-on-raspberry-64-os.html).<br><br>
Or, when you have no intentions to program code:
```
$ sudo apt-get install lib-opencv-dev 
```
#### RKLLM, RKNN
```
$ git clone https://github.com/airockchip/rknn-toolkit2.git
```
We only use a few files.
```
rknn-toolkit2-master
│      
└── rknpu2
    │      
    └── runtime
        │       
        └── Linux
            │      
            └── librknn_api
                ├── aarch64
                │   └── librknnrt.so
                └── include
                    ├── rknn_api.h
                    ├── rknn_custom_op.h
                    └── rknn_matmul_api.h

$ cd ~/rknn-toolkit2-master/rknpu2/runtime/Linux/librknn_api/aarch64
$ sudo cp ./librknnrt.so /usr/local/lib
$ cd ~/rknn-toolkit2-master/rknpu2/runtime/Linux/librknn_api/include
$ sudo cp ./rknn_* /usr/local/include
```
Save 2 GB of disk space by removing the toolkit. We do not need it anymore.
```
$ cd ~
$ sudo rm -rf ./rknn-toolkit2-master
```

------------

## Installing the app.
To extract and run the network in Code::Blocks <br/>
```
$ mkdir *MyDir* <br/>
$ cd *MyDir* <br/>
$ git clone https://github.com/Qengineering/YoloV5-NPU.git <br/>
```

------------

## Running the app.
You can use **Code::Blocks**.
- Load the project file *.cbp in Code::Blocks.
- Select _Release_, not Debug.
- Compile and run with F9.
- You can alter command line arguments with _Project -> Set programs arguments..._ 

Or use **Cmake**.
```
$ cd *MyDir*
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
```
Make sure you use the model fitting your system.<br><br>

------------

## VLM examples.
| Image         | Dialog |
| --------------| --  |
| ![Singapore_S](https://github.com/user-attachments/assets/e742059a-3bdb-41be-9647-e7767da12ce6) |**User**: <image>Which city is this?<br>**Answer**: This image shows Singapore's iconic skyline at sunset. The distinctive Marina Bay Sands and the ArtScience Museum are prominent landmarks in Singapore. | 
| ![ChineseWall_S](https://github.com/user-attachments/assets/3ba4b57a-4b22-4050-b995-9599c6d239de) |**User**: <image>Tell me something about the history of this place.<br>**Answer**: The Great Wall of China is an ancient defensive structure that has been built over thousands of years to protect against invasions from northern nomadic tribes. The wall stretches across central China, connecting the north and south of the country. It was constructed by the Chinese dynasties during the Qin Dynasty (221-206 BCE) and later expanded under various rulers including the Ming Dynasty (1368-1644). The Great Wall is not only a testament to engineering prowess but also a symbol of China's historical resilience and cultural heritage.|
| ![Pizza_S](https://github.com/user-attachments/assets/26fd5da3-f491-4b48-978a-14eae0819247) |**User**: <image>What are the ingredients I need to make this?<br>**Answer**: To make this pizza, you'll need:<br>1. **Pizza Dough**: This is typically made from flour, water, yeast, and other ingredients.<br> 2. **Tomato Sauce**: A rich tomato-based sauce that provides flavor and color.<br> 3. **Cheese**: Mozzarella or another type of cheese for the melted cheese topping.<br> 4. **Fresh Basil Leaves**: For garnish and added freshness.<br>You can also add toppings like pepperoni, mushrooms, olives, or meats depending on your preference.<br><br>**User**: What is the first step?<br>**Answer**: The first step to making this pizza involves preparing the dough. Here's what you'll need:<br>1. **Prepare the Dough**:<br>**Ingredients**:<br>2 cups of all-purpose flour<br>3 teaspoons of active dry yeast<br>4 tablespoons of warm water (around 105°F to 115°F)<br>1 teaspoon of salt<br>**Instructions**:<br>1. In a large mixing bowl, combine the flour and salt.<br>2. Add the warm water and yeast mixture, stirring until the dough starts to come together.<br>3. Knead the dough on a floured surface for about 5 minutes, until it becomes smooth and elastic.<br>4. Place the dough in a lightly oiled bowl, cover with a damp cloth, and let it rise in a warm place for about 1 hour, or until doubled in size.<br>This will give you a soft, elastic pizza crust that will be great for your delicious homemade pizza!|
| ![Titanic_S](https://github.com/user-attachments/assets/bf6da76c-c9a4-41c6-bea1-2b4411dd4013) |**User**: <image>Which movie is this?<br>**Answer**: This image appears to be from the movie "The Little Mermaid." It shows two characters on a ship at sunset, with one reaching out towards the sea. The setting and costumes suggest it's from the Disney film series.|

## LLM example.
Notice the nice Markdown makeup of the answer!<br><br>
**User**: Can you make me a C++ call that embeds the Pythagorean theorem?<br><br>
**Answer**: Certainly! The Pythagorean theorem is a fundamental principle in geometry stating that in a right-angled triangle, the square of the length of the hypotenuse (the side opposite the right angle) is equal to the sum of the squares of the lengths of the other two sides. In mathematical terms:

\[ c^2 = a^2 + b^2 \]

where \( c \) is the length of the hypotenuse, and \( a \) and \( b \) are the lengths of the other two sides.

To implement this in C++, you can use the following code snippet. This example will calculate the distance between two points using the Pythagorean theorem:

```cpp
#include <iostream>
#include <cmath> // For sqrt function

// Function to calculate the Euclidean distance between two points (x1, y1) and (x2, y2)
double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    // Coordinates of the two points
    double x1 = 3.0;
    double y1 = 4.0;
    double x2 = 6.0;
    double y2 = 8.0;

    // Calculate the distance using the Pythagorean theorem
    double distance = calculateDistance(x1, y1, x2, y2);

    // Output the result
    std::cout << "The distance between points (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ") is: " << distance << std::endl;

    return 0;
}
```

### Explanation:
1. **Include Necessary Headers**: The `#include <iostream>` header is used for input-output operations, and the `#include <cmath>` header provides access to mathematical functions like `sqrt`.

2. **Function Definition**:
   - `double calculateDistance(double x1, double y1, double x2, double y2)`: This function takes four parameters representing the coordinates of two points in a 2D plane and returns the Euclidean distance between them.

3. **Main Function**:
   - The main function initializes the coordinates of the two points.
   - It then calls `calculateDistance` to compute the distance using the Pythagorean theorem.
   - Finally, it prints out the calculated distance.

This code will output the distance between the points (3, 4) and (6, 8), which is approximately 5.196152.

Feel free to modify the coordinates or use this as a starting point for other geometric calculations!

------------

[![paypal](https://qengineering.eu/images/TipJarSmall4.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CPZTM5BB3FCYL) 




