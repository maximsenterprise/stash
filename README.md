# Stash
## Powerful Web Engine

Stash aims to be a powerful web rendering model that can render webpages at a glance. Currently is not for release and the project its barley started.

Stash is made out of three components: Two 'platform-independent' components, and one 'platform-dependent' component.

### What makes Stash

Stash is made out of:

- **Flux**: Gets the data from the server (thanks to curl!)
- **Convex**: Renders the webpage
- **Amethyst**: Our custom JavaScript, TypeScript and WebAssembly runtime.

Convex depends on the platform to render:

- For **macOS** we use *Objective-C++* toghether with *Cocoa* to render the page. `/macOS`

### How to build and execute?

Firstly, there are two ways to bundle Stash. First one is for tests. This executable is called `tailor`.

**To build Tailor**: `cmake . -Dtailor`. This will generate an executable in the build folder called `tailor`.
If you are in the main folder give it a try with `./build/tailor google.com`. This will render the page.

Secondly, try to integrate it with your own projects. This is a simple example of how to render google.

```c++
#include "convex.hpp"
#include "flux.hpp"
#include <string>

int main() {
    std::string html = flux::get_html("google.com");
    std::vector<convex::HTMLNode> nodes = convex::parse_html(html);
    convex::render_to_screen(nodes);
}
```
Then make sure to add your file to the `CMakeList` source list and to change the output file.

