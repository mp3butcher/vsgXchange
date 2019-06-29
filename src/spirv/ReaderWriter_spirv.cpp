#include <vsgXchange/ReaderWriter_spirv.h>

#include <vsg/vk/ShaderStage.h>

#include <iostream>

using namespace vsgXchange;

ReaderWriter_spirv::ReaderWriter_spirv()
{
}

vsg::ref_ptr<vsg::Object> ReaderWriter_spirv::readFile(const vsg::Path& filename) const
{
    std::cout<<"ReaderWriter_spirv::readFile("<<filename<<")"<<std::endl;

    auto ext = vsg::fileExtension(filename);
    if (ext=="spv" && vsg::fileExists(filename))
    {
        vsg::ShaderModule::SPIRV spirv;
        vsg::readFile(spirv, filename);

        auto sm = vsg::ShaderModule::create(spirv);
        return sm;
    }
    return vsg::ref_ptr<vsg::Object>();
}

bool ReaderWriter_spirv::writeFile(const vsg::Object* object, const vsg::Path& filename) const
{
    std::cout<<"ReaderWriter_spirv::writeFile("<<object->className()<<", "<<filename<<")"<<std::endl;

    auto ext = vsg::fileExtension(filename);
    if (ext=="spv")
    {
        const vsg::ShaderStage* ss = dynamic_cast<const vsg::ShaderStage*>(object);
        const vsg::ShaderModule* sm = ss ? ss->getShaderModule() : dynamic_cast<const vsg::ShaderModule*>(object);
        if (sm)
        {
            if (!sm->spirv().empty())
            {
                std::ofstream fout(filename);
                fout.write(reinterpret_cast<const char*>(sm->spirv().data()), sm->spirv().size() * sizeof(vsg::ShaderModule::SPIRV::value_type));
                fout.close();
                return true;
            }
        }
    }
    return false;
}
