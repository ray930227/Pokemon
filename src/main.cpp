#include "App.hpp"
#include "SFXSystem.hpp"

#include "Core/Context.hpp"

int main(int, char **) {
    auto context = Core::Context::GetInstance();
    App app;
    SFXSystem SFX;

    while (!context->GetExit()) {
        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            SFX.Play("Click");
        }
        switch (app.GetCurrentState()) {
            case App::State::START:
                app.Start();
                break;

            case App::State::HOME:
                app.Home();
                break;

            case App::State::READ_SAVE:
                app.ReadSave();
                break;

            case App::State::INIT:
                app.Init();
                break;

            case App::State::UPDATE:
                app.Update();
                break;

            case App::State::EVENT:
                app.Event();
                break;

            case App::State::LOADING:
                app.Loading();
                break;

            case App::State::FIGHT:
                app.Fight();
                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
