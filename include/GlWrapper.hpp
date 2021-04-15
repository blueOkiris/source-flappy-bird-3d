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
        
        template<class T>
        struct Vector3 {
            T x, y, z;
        };
        typedef Vector3<uint> Vector3u;
        typedef Vector3<int> Vector3i;
        typedef Vector3<float> Vector3f;
        typedef Vector3<double> Vector3d;
        
        struct Color {
            float r, g, b, a;
        };
        
        inline void loadIdentity(void) {
            glLoadIdentity();
        }
        
        inline void clear(const Color bg = { 0, 0, 0, 1.0 }) {
            glClearColor(bg.r, bg.g, bg.b, bg.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        
        inline void display(void) {
            glutSwapBuffers();
        }
        
        inline void pushQuads(const std::vector<Vector3f> &verts) {
            glBegin(GL_QUADS);
            for(const auto vert : verts) {
                glVertex3f(vert.x, vert.y, vert.z);
            }
            glEnd();
        }
        
        inline void pushTris(const std::vector<Vector3f> &verts) {
            glBegin(GL_TRIANGLES);
            for(const auto vert : verts) {
                glVertex3f(vert.x, vert.y, vert.z);
            }
            glEnd();
        }
        
        inline void rotate(const float angle, const Vector3f axis) {
            glRotatef(angle, axis.x, axis.y, axis.z);
        }
        
        namespace utility {
            inline void lookAt(
                    const gl::Vector3d eye, const Vector3d center,
                    const Vector3d up) {
                gluLookAt(
                    eye.x, eye.y, eye.z,
                    center.x, center.y, center.z,
                    up.x, up.y, up.z
                );
            }
        }
    }
    
    namespace glut {
        enum class Key {
            Escape = 27
        };
        
        typedef int WindowId;
        inline void init(int *argc, char **args) {
            glutInit(argc, args);
        }
        
        class Window {
            private:
                static void _changeSize(const int width, const int height);
                
                const WindowId _id;
            
            public:
                Window(
                    const std::string &title,
                    const gl::Vector2i initSize, const gl::Vector2i initPos
                );
                
                void run(
                    void (*displayFunc)(void),
                    void (*keyboardFunc)(const uint8_t, const int, const int),
                    void (*mouseFunc)(
                        const int, const int, const int, const int
                    )
                ) const;
        };
    }
}
