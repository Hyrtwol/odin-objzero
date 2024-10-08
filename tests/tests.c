/*
https://github.com/jpcy/objzero

Copyright (c) 2018 Jonathan Young
Copyright (c) 2012-2018 Syoyo Fujita and many contributors.

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <stdio.h>
#include "..\objzero.c"

#define ASSERT(_condition) if (!(_condition)) printf("[FAIL] '%s' %s %d\n", #_condition, __FILE__, __LINE__);

int main(int argc, char **argv) {
	{
		printf("parseVertexAttribIndices\n");
		Token token;
		int32_t triplet[3];
		// optional texcoord and normal
		snprintf(token.text, sizeof(token.text), "1/2/3");
		ASSERT(parseVertexAttribIndices(&token, triplet));
		ASSERT(triplet[0] == 1);
		ASSERT(triplet[1] == 2);
		ASSERT(triplet[2] == 3);
		snprintf(token.text, sizeof(token.text), "1/2/");
		ASSERT(parseVertexAttribIndices(&token, triplet));
		ASSERT(triplet[0] == 1);
		ASSERT(triplet[1] == 2);
		ASSERT(triplet[2] == INT_MAX);
		snprintf(token.text, sizeof(token.text), "1/2");
		ASSERT(parseVertexAttribIndices(&token, triplet));
		ASSERT(triplet[0] == 1);
		ASSERT(triplet[1] == 2);
		ASSERT(triplet[2] == INT_MAX);
		snprintf(token.text, sizeof(token.text), "1//");
		ASSERT(parseVertexAttribIndices(&token, triplet));
		ASSERT(triplet[0] == 1);
		ASSERT(triplet[1] == INT_MAX);
		ASSERT(triplet[2] == INT_MAX);
		snprintf(token.text, sizeof(token.text), "1/");
		ASSERT(parseVertexAttribIndices(&token, triplet));
		ASSERT(triplet[0] == 1);
		ASSERT(triplet[1] == INT_MAX);
		ASSERT(triplet[2] == INT_MAX);
		snprintf(token.text, sizeof(token.text), "1");
		ASSERT(parseVertexAttribIndices(&token, triplet));
		ASSERT(triplet[0] == 1);
		ASSERT(triplet[1] == INT_MAX);
		ASSERT(triplet[2] == INT_MAX);
		snprintf(token.text, sizeof(token.text), "1//3");
		ASSERT(parseVertexAttribIndices(&token, triplet));
		ASSERT(triplet[0] == 1);
		ASSERT(triplet[1] == INT_MAX);
		ASSERT(triplet[2] == 3);
		// position isn't optional
		snprintf(token.text, sizeof(token.text), "/2/3");
		ASSERT(!parseVertexAttribIndices(&token, triplet));
		snprintf(token.text, sizeof(token.text), "/2/");
		ASSERT(!parseVertexAttribIndices(&token, triplet));
		snprintf(token.text, sizeof(token.text), "/2");
		ASSERT(!parseVertexAttribIndices(&token, triplet));
		snprintf(token.text, sizeof(token.text), "//3");
		ASSERT(!parseVertexAttribIndices(&token, triplet));
		snprintf(token.text, sizeof(token.text), "//");
		ASSERT(!parseVertexAttribIndices(&token, triplet));
		snprintf(token.text, sizeof(token.text), "/");
		ASSERT(!parseVertexAttribIndices(&token, triplet));
        token.text[0] = 0;
		ASSERT(!parseVertexAttribIndices(&token, triplet));
	}
	printf("Done\n");
	return 0;
}
