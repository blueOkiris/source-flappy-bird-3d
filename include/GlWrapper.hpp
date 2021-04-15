#include <string>
#include <vector>
#include <GL/glut.h>

namespace flappybird {
    namespace gl {
        template<class T>
        struct Vector2 {
            T x, y;
        };
        typedef Vector2<uint> Vector2u;
        typedef Vector2<int> Vector2i;
        typedef Vector2<float> Vector2f;
        
        struct Color {
            float r, g, b, a;
        };
        
        inline void clear(const Color bg = { 0, 0, 0, 1.0 }) {
            glClearColor(bg.r, bg.g, bg.b, bg.a);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        
        inline void display(void) {
            glFlush();
        }
        
        inline void pushQuads(const std::vector<Vector2f> &verts) {
            glBegin(GL_QUADS);
            for(const auto vert : verts) {
                glVertex2f(vert.x, vert.y);
            }
            glEnd();
        }
    }
    
    namespace glut {
        typedef int WindowId;
        inline void init(int *argc, char **args) {
            glutInit(argc, args);
        }
        
        class Window {
            private:
                const WindowId _id;
            
            public:
                Window(
                    const std::string &title,
                    const gl::Vector2i initSize, const gl::Vector2i initPos,
                    void (*displayFunc)(void)
                );
                
                void run(void) const;
        };
    }
}
