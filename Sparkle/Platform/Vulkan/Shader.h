#pragma once

#include "Common.h"
#include "Core.h"

#include "Render/Shader.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class Shader : public SuperShader
        {

        public:

            Shader(Device *device, const std::string &filename, Type type = Type::Graphics);

            virtual ~Shader();

            VkShaderModule Load(const std::string &filename, Stage stage);

            VkPipelineShaderStageCreateInfo CreateStage(VkShaderModule module, VkShaderStageFlagBits stage);

            auto &GetStages()
            {
                return stages;
            }

            const std::vector<VkDescriptorPoolSize> &PoolSize() const
            {
                return poolSizes;
            }

        private:
            void Reflect(const std::string &source);

            void SetupDescriptorSetLayout(Stage stage);

            void Setup();

        private:

            Device *device{ nullptr };

            std::vector<VkShaderModule> modules;

            std::vector<Shader::Resource> resources;

            std::vector<VkPipelineShaderStageCreateInfo> stages;

            //PipelineLayout pipelineLayout;

            VkDescriptorSetLayout descriptorSetLayout;

            //DescriptorSetUpdater descriptorSetUpdater;

            std::vector<VkDescriptorPoolSize> poolSizes;

            std::vector<VkPushConstantRange> pushConstantRanges;

            std::vector<VkDescriptorSetLayoutBinding> descriptorSetLayoutBindings;
        };

    } // SPK
} // Vulkan
