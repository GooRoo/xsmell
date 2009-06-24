XSMELL README
-------------

Congratulations! You have in your hands the MOST BRILLIANTEST C++ XML CREATION 
LIBRARY EVER CREATED.

Have you ever needed to embed a quick snippet of HTML or XML in your C++ source 
code? Didn't you just hate having to use that obscure string concatenation
syntax?

Well no more! With the advent of XSMELL you can now use regular XML syntax
directly in your source code, thanks to the reckless use of operator 
overloading, template meta-programming and preprocessor macros:

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

That's right! Thanks to XSMELL you'll no longer suffer from S-Expression
envy. You've got one up on those Lisp guys now -- smug bastards!

And you no longer have to worry about generating malformed XML! After spending
hours fighting obscure C++ compiler errors, you'll be 100% certain that your 
XML is correct.

NOTE: XSMELL requires Boost headers and a modern C++ compiler with support for 
C99 variadic macros.
