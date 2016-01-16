/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "Shell.h"

#include <Rocket/Core/Core.h>
#include <Rocket/Core/FreeType/FontProvider.h>
#include <Rocket/Core/BitmapFont/FontProvider.h>
#include "ShellFileInterface.h"

#include <sys/time.h>
#include <stdio.h>

Rocket::Core::String Shell::executable_path;

ShellFileInterface* file_interface = NULL;

/// Loads the default fonts from the given path.
void Shell::LoadFonts(const char* directory)
{
    Rocket::Core::String font_names[4];
    font_names[0] = "Delicious-Roman.otf";
    font_names[1] = "Delicious-Italic.otf";
    font_names[2] = "Delicious-Bold.otf";
    font_names[3] = "Delicious-BoldItalic.otf";

	for (int i = 0; i < sizeof(font_names) / sizeof(Rocket::Core::String); i++)
	{
        Rocket::Core::FreeType::FontProvider::LoadFontFace(Rocket::Core::String(directory) + font_names[i]);
	}
}


/// Loads the default fonts from the given path.
void Shell::LoadBitmapFonts(const char* directory)
{
    Rocket::Core::String font_names[1];
    font_names[0] = "arial_latin.fnt";

    for (int i = 0; i < sizeof(font_names) / sizeof(Rocket::Core::String); i++)
    {
        Rocket::Core::BitmapFont::FontProvider::LoadFontFace(Rocket::Core::String(directory) + font_names[i]);
    }
}

// Returns the path to the application's executable.
const Rocket::Core::String& Shell::GetExecutablePath()
{
	return executable_path;
}

void Shell::DisplayError(const char* fmt, ...)
{
    const int buffer_size = 1024;
    char buffer[buffer_size];
    va_list argument_list;
    
    // Print the message to the buffer.
    va_start(argument_list, fmt);
    int len = vsnprintf(buffer, buffer_size - 2, fmt, argument_list);
    if (len < 0 || len > buffer_size - 2)
    {
        len = buffer_size - 2;
    }
    buffer[len] = '\n';
    buffer[len + 1] = '\0';
    va_end(argument_list);
    
    printf("%s", buffer);
}

void Shell::Log(const char* fmt, ...)
{
    const int buffer_size = 1024;
    char buffer[buffer_size];
    va_list argument_list;
    
    // Print the message to the buffer.
    va_start(argument_list, fmt);
    int len = vsnprintf(buffer, buffer_size - 2, fmt, argument_list);
    if ( len < 0 || len > buffer_size - 2 )
    {
        len = buffer_size - 2;
    }
    buffer[len] = '\n';
    buffer[len + 1] = '\0';
    va_end(argument_list);
    
    printf("%s", buffer);
}

float Shell::GetElapsedTime()
{
    static bool initalised = false;
    static timeval start_time;
    if (!initalised)
    {
        initalised = true;
        gettimeofday(&start_time, NULL);

    }
    
    struct timeval now;
    
    gettimeofday(&now, NULL);
    
    double sec = now.tv_sec - start_time.tv_sec;
    double usec = now.tv_usec;
    double result = sec + (usec / 1000000.0);
    
    return (float) result;
}


