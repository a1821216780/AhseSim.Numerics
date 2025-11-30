// <copyright file="OpenBlasLinearAlgebraControl.cs" company="AHSEsim">
// AHSEsim Numerics, part of the AHSEsim Project
// https://numerics.mathdotnet.com
// https://github.com/mathnet/mathnet-numerics
//
// Copyright (c) 2009-2021 AHSEsim
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// </copyright>

using System;
using AHSEsim.Numerics.Providers.LinearAlgebra;

namespace AHSEsim.Numerics.Providers.OpenBLAS.LinearAlgebra
{
    public class OpenBlasLinearAlgebraControl : IProviderCreator<ILinearAlgebraProvider>
    {
        public static ILinearAlgebraProvider CreateNativeOpenBLAS() => new OpenBlasLinearAlgebraProvider(GetCombinedHintPath());
        public static void UseNativeOpenBLAS() => LinearAlgebraControl.Provider = CreateNativeOpenBLAS();
        public static bool TryUseNativeOpenBLAS() => LinearAlgebraControl.TryUse(CreateNativeOpenBLAS());

        static string GetCombinedHintPath()
        {
            if (!string.IsNullOrEmpty(OpenBlasControl.HintPath))
            {
                return OpenBlasControl.HintPath;
            }

            if (!string.IsNullOrEmpty(LinearAlgebraControl.HintPath))
            {
                return LinearAlgebraControl.HintPath;
            }

            var value = Environment.GetEnvironmentVariable(OpenBlasControl.EnvVarOpenBLASProviderPath);
            if (!string.IsNullOrEmpty(value))
            {
                return value;
            }

            return null;
        }

        public ILinearAlgebraProvider CreateProvider() => CreateNativeOpenBLAS();
    }
}
