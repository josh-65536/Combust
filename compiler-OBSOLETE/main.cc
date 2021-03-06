#include "code-lexer.hh"
#include "logger.hh"
#include "source.hh"
#include "syntax.hh"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *g_ProgramName;

static void PreprocessFile(const char* filePath) {
    Rc<SourceFile> sourceFile{ OpenSourceFile(filePath) };
    if (sourceFile == nullptr) {
        Log(LL_FATAL, "cannot open %s", filePath);
        return;
    }

    Rc<CodeLexer> lexer{ NewObj<CodeLexer>(sourceFile) };

    Rc<SyntaxToken> t{ };
    do {
        t = lexer->ReadToken();
    }
    while (!IsSyntaxNode<EofToken>(t));
}

int main(int argc, char** argv) {
    g_ProgramName = argv[0];

    if (argc == 1) {
        printf("compiler v0.3-SNAPSHOT\n");
        printf("\
Usage: %s [options] file...\n\
Options:\n\
", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i{ 1 }; i < argc; ++i) {
        PreprocessFile(argv[i]);
    }

    return g_ErrorsLogged ? EXIT_FAILURE : EXIT_SUCCESS;
}
