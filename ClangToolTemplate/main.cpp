//
//  main.cpp
//  ASTMatchersTest
//
//  Created by Hendrik von Prince on 10.05.14.
//  Copyright (c) 2014 Hendrik von Prince. All rights reserved.
//

#include <iostream>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/ADT/OwningPtr.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/JSONCompilationDatabase.h>
#include <clang/Tooling/Tooling.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/AST.h>
#include <clang/Basic/SourceManager.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchersInternal.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

using namespace clang;
using namespace tooling;

int main(int argc, const char * argv[])
{
    // set the relative path to the compilation-database
    // by default, it is assumed that the compilation-database is named compilation_database.json and resides within the current directory
    const std::string pathToCompilationDB= "compilation_database.json";
    
    std::string errorMessage;
    llvm::OwningPtr<JSONCompilationDatabase> db(JSONCompilationDatabase::loadFromFile(pathToCompilationDB, errorMessage));
    if(db.isValid()== false) {
        std::cout << errorMessage << std::endl;
        return EXIT_FAILURE;
    }
    
    ClangTool tool(*db, db->getAllFiles());

    tool.run(newFrontendActionFactory<SyntaxOnlyAction>().get());
    
    return 0;
}

