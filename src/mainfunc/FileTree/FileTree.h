#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <functional>
#include <chrono>

class FileTree {
public:
    static std::string clickedFileName;
    using FileClickCallback = std::function<void(const std::string&)>;

    static void treeNode();
    static void setFileClickCallback(FileClickCallback callback);

private:
    static std::string filePath;

    struct FileNode 
    {
        std::string name;
        std::string path;
        std::vector<FileNode> children;
        bool isUnsaved = false;  // New flag to indicate unsaved status
        bool isDirectory;

        // Default constructor
        FileNode() : isDirectory(false) {}

        // User-defined constructor
        FileNode(const std::string& name, const std::string& path, bool isDirectory)
            : name(name), path(path), isDirectory(isDirectory) {}
    };

    static FileNode TraverseDirectory(const boost::filesystem::path& directory);
    static void RenderFileNode(FileNode& node);
    static void UpdateTree();

    static FileNode rootNode;
    static inline bool isInitialized = false;

    static FileClickCallback fileClickCallback;

    static inline std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime;
    static inline std::chrono::milliseconds updateInterval{ 1000 }; //Update interval of 1 second
};