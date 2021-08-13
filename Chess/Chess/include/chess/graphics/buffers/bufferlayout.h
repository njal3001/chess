#include <GL/glew.h>
#include <vector>
#include <iostream>

namespace Chess
{
    namespace Graphics
    {
        struct LayoutElement
        {
            GLint count;
            GLenum type;
            GLboolean normalized;
            unsigned int offset;
        };

        class BufferLayout
        {
        private:
            std::vector<LayoutElement> m_elements;
            GLsizei m_stride;

        public:
            BufferLayout();

            void push(GLenum type, int count, GLboolean normalized);
            const std::vector<LayoutElement>& get_elements() const;
            GLsizei get_stride() const;
        };

    }
}
