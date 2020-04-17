#include "Viewer.hpp"

rt::Viewer::Viewer(const Scene &scene, const Camera &camera)
    : _scene(scene), _camera(camera)
{

}

void rt::Viewer::show(
    std::unique_ptr<IGraphicalLibrary> &graphicLibrary,
    std::unique_ptr<Renderer> &renderer)
{
    // Render scene
    if (_scene.hasChangedSinceLastFrame())
        renderer->render(_scene, _camera);

    // Display the resulting scene
    graphicLibrary->clear(Color::Black);
    graphicLibrary->draw(renderer->frameBuffer());
    graphicLibrary->display();
}