#include <cstdlib> // for setenv
#include <iostream>
#include <pybind11/embed.h> // Pybind11 for Python embedding
#include <string>

namespace py = pybind11;

int main()
{
    // Set environment variables to use the correct Anaconda environment
    setenv("PYTHONHOME", "/root/anaconda3/envs/pytorch", 1);
    setenv("PYTHONPATH", "/root/anaconda3/envs/pytorch/lib/python3.8/site-packages", 1);

    // Initialize the Python interpreter
    py::scoped_interpreter guard{};

    try {
        // Set Python path to include the project directory and dependencies
        py::module sys = py::module::import("sys");
        // sys.attr("path").attr("clear")(); // 清除原有路径，防止冲突
        sys.attr("path").attr("append")("/root/anaconda3/envs/pytorch/lib/python3.8/site-packages");
        sys.attr("path").attr("append")("/root/anaconda3/envs/pytorch/lib/python3.8");
        sys.attr("path").attr("append")("/data1/zhn/macdata/code/github/python/TextRecognitionDataGenerator/FontClassify");
        sys.attr("path").attr("append")("/data1/zhn/macdata/code/github/python/TextRecognitionDataGenerator"); // Add the root directory for other dependencies

        std::cout << "PYTHONHOME: " << std::getenv("PYTHONHOME") << std::endl;
        std::cout << "PYTHONPATH: " << std::getenv("PYTHONPATH") << std::endl;

        // Import the predictsingle module
        py::module predict = py::module::import("predictsingle");

        // Call the predict function from predictsingle.py
        std::string model_path = "/data1/zhn/macdata/code/github/python/TextRecognitionDataGenerator/FontClassify/weights/best_model_acc0.9927_20240930-095649.pth";
        std::string image_path = "/data1/zhn/macdata/code/github/python/TextRecognitionDataGenerator/outEval/FangSong/ 货 服 蓉 尚 嚣 龄 野 抹_1758.jpg";

        // Assuming the function in predictsingle.py is called "predict" and takes model_path and image_path as arguments
        py::object result = predict.attr("main_predict")(model_path, image_path);

        // Print the result (assuming it's a string or can be cast to one)
        std::cout << "Prediction result: " << result.cast<std::string>() << std::endl;
    } catch (const py::error_already_set& e) {
        // Handle Python errors
        std::cerr << "Python error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}