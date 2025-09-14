#include <iostream>
#include <string>

// 子系统 1
class VideoSystem
{
public:
    std::string initial() const
    {
        return "Video System:Ready!\n";
    }
    std::string play() const
    {
        return "Video System:go!\n";
    }
    std::string operationX() const
    {
        return "Video System:not unusual!\n";
    }
};

// 子系统 2
class RadioSystem
{
public:
    std::string init() const
    {
        return "Radio System:Ready!\n";
    }
    std::string play() const
    {
        return "Radio System:go!\n";
    }
    std::string operationX() const
    {
        return "Radio System:not unusual!\n";
    }
    std::string mute() const
    {
        return "Radio System:mute!\n";
    }
};

class Controller
{
protected:
    VideoSystem *m_video;
    RadioSystem *m_radio;

public:
    Controller(VideoSystem *video = nullptr, RadioSystem *radio = nullptr)
    {
        if (!video)
            m_video = video;
        else
            new VideoSystem;

        m_radio = radio ? radio : new RadioSystem;
    }
    ~Controller()
    {
        delete m_video;
        delete m_radio;
    }
    std::string start()
    {
        std::string string = "控制器启动系统:\n";
        string += m_video->initial();
        string += m_radio->init();
        string += "控制器播放\n";
        string += m_video->play();
        string += m_radio->play();
        return string;
    }
    std::string mute()
    {
        return m_radio->mute();
    }
};

int main()
{
    VideoSystem *videoSystem = new VideoSystem();
    RadioSystem *radioSystem = new RadioSystem();
    Controller controller(videoSystem, radioSystem); // 外观对象,负责回收子系统
    std::cout << controller.start();
    return 0;
}