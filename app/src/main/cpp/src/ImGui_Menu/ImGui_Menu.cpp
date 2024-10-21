#include <iostream>
#include <cstdlib>
#include <vector>
#include "ImGui_Menu.h"
static  ImGuiWindowFlags windowflags =  ImGuiWindowFlags_NoTitleBar |
ImGuiWindowFlags_NoResize |
ImGuiWindowFlags_NoScrollWithMouse |
ImGuiWindowFlags_NoCollapse;

static float beginHeight  = 0.0f;
std::string hint = {};

// 定义面板状态
enum PanelState
{
    None,
    Authorization,
    Data,
    Login,
    Customization,
    Features,
    Setting,
};

// 定义主题数量
const int THEME_COUNT = 2;
const char *themes[THEME_COUNT] = {"Theme 1", "Theme 2"};

// 边框配置结构体
struct BorderConfig
{
    bool show = true;
    float radius = 5.0f;
    // 默认构造函数
    BorderConfig() : show(true), radius(5.0f) {}

    // 带参数的构造函数
    BorderConfig(bool show, float radius) : show(show), radius(radius) {}
};

// 窗口配置结构体
struct WindowConfig
{
    ImVec2 mainWindowSize = ImVec2(600, 450);
    ImVec2 tabsSize = ImVec2(150, 400);
    ImVec2 contentSize = ImVec2(420, 400);
    BorderConfig mainBorder = {true, 5.0f};
    BorderConfig tabsBorder = {true, 5.0f};
    BorderConfig contentBorder = {false, 5.0f};
};

// 全局变量
int curButton = 0;
int curTheme = 0;
char buf[128] = "";
WindowConfig config;

// 功能页面基类
class Panel
{
public:
    virtual ~Panel() {}
    virtual void Render() = 0; // 纯虚函数，派生类需要实现
};

// 授权面板
class AuthorizationPanel : public Panel
{
public:
    void Render() override
    {
        ImGui::BeginChild("AuthorizationWindow", ImVec2(config.contentSize.x - 20, config.contentSize.y - 20), config.contentBorder.show);
        ImGui::SetCursorPos(ImVec2(150, 16));
        ImGui::Text("   Authorization");
        ImGui::SetCursorPos(ImVec2(150, 38));
        ImGui::Text("  Enter your key");
        ImGui::SetCursorPos(ImVec2(19, 60));
        ImGui::InputText("###Key", buf, IM_ARRAYSIZE(buf));
        ImGui::SetCursorPos(ImVec2(125, 95));
        if (ImGui::Button("Sign in", ImVec2(165, 40)))
        {
            // 处理登录逻辑
        }
        ImGui::SetCursorPos(ImVec2(120, 200));
        ImGui::Text("   Subscribe Expire Day");
        ImGui::EndChild();
    }
};

// 数据面板
class DataPanel : public Panel
{
public:
    void Render() override
    {
        ImGui::BeginChild("DataWindow", ImVec2(config.contentSize.x - 20, config.contentSize.y - 20), config.contentBorder.show);
        if (ImGui::Button("Exit", ImVec2(80, 60)))
        {
            exit(0);
        };
        ImGui::SetCursorPos(ImVec2(148, 10));
        ImGui::Text("   Welcome User.");
        ImGui::SetCursorPos(ImVec2(150, 28));
        ImGui::Text("     DashBoard:");
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(200, 90), ImVec2(518, 206), IM_COL32(255, 0, 0, 40));
        ImGui::SetCursorPos(ImVec2(0, 60));
        ImGui::Text("                    -          Added 1tick doubletap.");
        ImGui::Text("                    -          Added Neverlose resolver.");
        ImGui::Text("                    -          Added Nemesis fakelag.");
        ImGui::Text("                    -          Added gamesense api.");
        ImGui::SetCursorPos(ImVec2(0, 180));
        ImGui::Text("    Cheat: Simplicity External / Game: CS:GO / Version: 1.0");
        ImGui::EndChild();
    }
};

// 自定义面板
class CustomizationPanel : public Panel
{
public:
    void Render() override
    {
        ImGui::BeginChild("CustomizableWindow", ImVec2(config.contentSize.x - 20, config.contentSize.y - 20), config.contentBorder.show);
        ImGui::SetCursorPos(ImVec2(120, 16));
        ImGui::Text("    Menu Customization");
        ImGui::SetCursorPos(ImVec2(16, 38));
        ImGui::Combo("Menu Theme", &curTheme, themes, THEME_COUNT);
        ImGui::EndChild();
    }
};

// 授权面板
class SettingPanel : public Panel
{
public:
    void Render() override
    {
        ImGuiStyle &style = ImGui::GetStyle();

        ImGui::BeginChild("SettingPanelWindow", ImVec2(config.contentSize.x - 20, config.contentSize.y - 20), config.contentBorder.show);

        ImGui::Text("Rounding");
        ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");

        ImGui::EndChild();
    }
};

// 授权面板
class LoginPanel : public Panel
{
public:
    void TextCentered(const char *text)
    {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::TextUnformatted(text);
    }

    // 绘制模糊背景
    void DrawBlurredBackground()
    {
        // 获取当前窗口位置和大小
        ImVec2 pos = ImGui::GetWindowPos();
        ImVec2 size = ImGui::GetWindowSize();

        // 模糊效果的透明度
        ImU32 bgColor = IM_COL32(24, 24, 26, 220);

        // 绘制模糊背景
        ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), bgColor);
    }

    void Render() override
    {
        ImGuiStyle &style = ImGui::GetStyle();

        // 计算窗口的大小
        ImVec2 windowSize = ImVec2(config.contentSize.x - 20, config.contentSize.y - 20);
        ImVec2 windowPos = ImVec2(
            (ImGui::GetWindowSize().x - windowSize.x) * 0.5f, // 横向居中
            (ImGui::GetWindowSize().y - windowSize.y) * 0.5f  // 纵向居中
        );

        // 设置窗口位置
        ImGui::SetCursorPos(windowPos);

        ImGui::BeginChild("LoginWindow", windowSize, config.contentBorder.show);

        // 绘制模糊背景
        this->DrawBlurredBackground();

        // 绘制圆角框
        ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + windowSize.x, ImGui::GetWindowPos().y + windowSize.y), 10.0f);

        // 使用设置的文本居中函数
        this->TextCentered("登录界面");
        ImGui::Spacing();

        static char username[128] = "";
        static char password[128] = "";

        ImGui::SetWindowFontScale(1.5f); // 设置字体大小可选

        // 创建一个包含输入框的水平布局
        ImGui::SetCursorPosX((windowSize.x - 200) * 0.5f); // 150 是输入框的宽度
        ImGui::Text("Username");
        ImGui::SetCursorPosX((windowSize.x - 200) * 0.5f); // 150 是输入框的宽度
        ImGui::InputText("##Username", username, IM_ARRAYSIZE(username));

        ImGui::SetCursorPosX((windowSize.x - 200) * 0.5f);
        ImGui::Text("Password");
        ImGui::SetCursorPosX((windowSize.x - 200) * 0.5f);
        ImGui::InputText("##Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

        // 添加与上一个输入框的间距
        ImGui::Spacing(); // 可以根据需要调整间距

        ImGui::SetCursorPosX((windowSize.x - 80) * 0.5f); // 150 是按钮的宽度
        if (ImGui::Button("Login", ImVec2(80, 30)))
        {
            // 处理登录逻辑
        }

        ImGui::EndChild();
    }
};

// 功能面板工厂
class PanelFactory
{
public:
    static Panel *CreatePanel(PanelState state)
    {
        switch (state)
        {
        case Authorization:
            return new AuthorizationPanel();
        case Data:
            return new DataPanel();
        case Customization:
            return new CustomizationPanel();
        case Setting:
            return new SettingPanel();
        case Login:
            return new LoginPanel();
        default:
            return nullptr;
        }
    }
};

// 绘制带圆角的边框
void DrawRoundedBorder(const ImVec2 &pos, const ImVec2 &size, float radius)
{
    ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), radius);
}

// 显示主窗口
void ShowMainWindowTwo(bool opened = true)
{
    ImGui::SetNextWindowSize(config.mainWindowSize, ImGuiCond_FirstUseEver);
    ImGui::Begin("Loader", &opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    // 绘制主窗口边框
    if (config.mainBorder.show)
        DrawRoundedBorder(ImGui::GetWindowPos(), config.mainWindowSize, config.mainBorder.radius);

    // 左侧按钮
    ImGui::BeginChild("TabsBar", config.tabsSize, config.tabsBorder.show);
    // 绘制标签栏边框
    if (config.tabsBorder.show)
        DrawRoundedBorder(ImGui::GetCursorScreenPos(), config.tabsSize, config.tabsBorder.radius);

    if (ImGui::Button("Authorization", ImVec2(130, 42)))
        curButton = Authorization;
    if (ImGui::Button("Data", ImVec2(130, 42)))
        curButton = Data;
    if (ImGui::Button("Customization", ImVec2(130, 42)))
        curButton = Customization;
    if (ImGui::Button("Setting", ImVec2(130, 42)))
        curButton = Setting;
    if (ImGui::Button("Login", ImVec2(130, 42)))
        curButton = Login;

    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("ContentArea", config.contentSize, config.contentBorder.show);

    // 绘制内容区域边框
    if (config.contentBorder.show)
        DrawRoundedBorder(ImGui::GetCursorScreenPos(), config.contentSize, config.contentBorder.radius);

    // 自定义背景
    ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(),
                                              ImVec2(ImGui::GetWindowPos().x + config.contentSize.x, ImGui::GetWindowPos().y + config.contentSize.y),
                                              IM_COL32(24, 24, 26, 255));

    // 根据当前按钮渲染对应的面板
    Panel *panel = PanelFactory::CreatePanel(static_cast<PanelState>(curButton));
    if (panel)
    {
        panel->Render();
        delete panel; // 使用完后释放内存
    }

    ImGui::EndChild();
    ImGui::End();
}


void ImGui_Menu::MainMenu() {
    float framerate = ImGui::GetIO().Framerate;
    if(beginHeight < 400.0f){
        beginHeight += 8.0f;
    }
    ImGui::SetNextWindowSize(ImVec2(500.0f,beginHeight));
    ImGui::Begin("Sak_Text_Input", nullptr,windowflags);
    ImGui::Text("FPS: %.1f", framerate);
    ImGui::InputTextWithHint("账号","请输入账号", this->account, IM_ARRAYSIZE(this->account));
    ImGui::InputTextWithHint("密码", "请输入密码", this->password, IM_ARRAYSIZE(this->password));
    if(ImGui::Button("登录")){
        if (strcmp(account, "") == 0 || strcmp(password, "") == 0) {
            hint = "账户名和密码不能为空!";
        } else if (strcmp(account, "root") == 0 && strcmp(password, "root") == 0){
            hint = "登录成功!";
            ShowMainWindowTwo(true);
        }else{
            hint = "账号密码错误!";
        }
    }
    ImGui::Text(hint.c_str());
    ImGui::End();
}
ImGui_Menu::ImGui_Menu(ImVec2* displaySize) {
    DisplaySize = displaySize;
}
