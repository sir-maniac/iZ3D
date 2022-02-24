cmake_minimum_required(VERSION 3.18)

project(dxerr CXX)

add_library(dxerr STATIC 
    dxerr.cpp  
    dxerr.h
    DXGetErrorDescription.inl
    DXGetErrorString.inl
    DXTrace.inl
)

set_property(TARGET dxerr PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
