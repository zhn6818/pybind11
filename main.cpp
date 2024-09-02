#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include <iostream>

namespace py = pybind11;

int main()
{
    py::scoped_interpreter guard {}; // Initialize the Python interpreter
    py::module_ sys = py::module_::import("sys");
    sys.attr("path").cast<py::list>().append(
        "/Volumes/data/code/github/python/pybind11");
    py::module py_script = py::module::import("example"); // Import Python module
    py::object result = py_script.attr("greet")(); // Call the Python function

    std::cout << "Result from Python: " << result.cast<std::string>() << std::endl;

    return 0;
}