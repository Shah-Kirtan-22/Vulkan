#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h> 

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // explicitly tell glfw to not create with GL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);  // disable window resizing
        
        window = glfwCreateWindow(WIDTH, HEIGHT, "Kirtan's Vulkan Window", nullptr, __nullptr);
    }

    void initVulkan() {
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void createInstance() {
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // applcation info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 3, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 3, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        // instance info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;  // an outer pointer which points to different inner pointers which point to const characters
        createInfo.enabledLayerCount = 0;

        // create vulkan instance
        VkResult result = vkCreateInstance(&createInfo, nullptr, &vulkanInstance);
        if (vkCreateInstance(&createInfo, nullptr, &vulkanInstance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
        else
        {
            std::cout << "Able to create a vulkan instance successfully" << std::endl;
        }
    }

    void cleanup() {
        vkDestroyInstance(vulkanInstance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    // constants
    const uint32_t WIDTH = 1920;
    const uint32_t HEIGHT = 1080;

    // init
    GLFWwindow* window;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    VkInstance vulkanInstance;
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}