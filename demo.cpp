// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://sam.zoy.org/wtfpl/COPYING for more details.

#include "xsmell.hpp"
#include <iostream>

TAG(html,  NO_ATTRIBS);
TAG(head,  NO_ATTRIBS);
TAG(title, NO_ATTRIBS);
TAG(body,  NO_ATTRIBS);
TAG(p,     NO_ATTRIBS);
TAG(a,     ATTRIB(href));
TAG(img,   ATTRIB(src), ATTRIB(alt));

int main()
{
    using namespace xsmell;

    document doc = 
        _
        <html>_
            <head>_
                <title>"XSMELL demo"<!title>_
            <!head>_
            <body>_
                <p>"Yesssssssssssssssss!"<!p>_
                <img .src("chucknorris.png") .alt("sneezing eyes open")>_ <!img>_
            <!body>_
        <!html>
        _;

    std::cout << doc << '\n';

    return 0;
}
