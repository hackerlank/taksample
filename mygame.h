#ifndef MYGAME_H__
#define MYGAME_H__

#include <tak.h>
#include "define.h"

class MyGame : public Game
{
    public:
        MyGame(const std::string& name, const std::string& version);
        virtual ~MyGame();

        virtual bool LoadResource();
        virtual bool UnloadResource();
        virtual void Update(float elapsedTime);
        virtual void KeyPressEvent(unsigned char key);
        virtual void KeyReleaseEvent(unsigned char key);
        virtual void MouseMoveEvent(int x, int y);
        virtual void MousePressEvent(const MOUSE_BUTTON &button, int x, int y);
        virtual void MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y);
        virtual void WindowFocusEvent(bool hasFocus);
        virtual void WindowResizeEvent(int width, int height);

        virtual Shader* GetDefaultShader();
        virtual Texture* GetDefaultTexture();

    private:
        int m_cubeCount;

        TextNode* m_txtFps;
        TextNode* m_txtCubeCount;
};

#endif // MYGAME_H__
