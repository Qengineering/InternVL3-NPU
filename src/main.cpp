#include "RK35llm.h"

//./CatDog.jpg ./models/InternVL3-1B/internvl3-1b_vision_fp16_rk3588.rknn ./models/InternVL3-1B/internvl3-1b_w8a8_rk3588.rkllm 2048 4096 3
//./car_6.jpg ../VLM/Qwen2-VL-2B/models/Qwen2-VL-2B_vision_rk3588.rknn ../VLM/Qwen2-VL-2B/models/Qwen2-VL-2B_llm_w8a8_rk3588.rkllm 2048 4096 3

int main(int argc, char** argv)
{
    std::string input_str;
    std::string output_str;
    RK35llm RKLLM;

    RKLLM.SetInfo(false);
    RKLLM.SetSilence(false);

    RKLLM.LoadModel(argv[2],argv[3]);

    cv::Mat Pic = cv::imread(argv[1]);
    RKLLM.LoadImage(Pic);

    while(true) {
        printf("\n");
        printf("user: ");

        std::getline(std::cin, input_str);
        if (input_str == "exit") break;

        output_str = RKLLM.Ask(input_str);
//        std::cout << "\nLLM Reply: " << output_str << std::endl;
    }

    return 0;
}
