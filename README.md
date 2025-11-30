AhseSim.Numerics
================

AHSEsim Numerics is an opensource **numerical library for .NET and Mono**.used for AHSEsim（Aero-hydro-serve-elastic coupled simulation)

AHSEsim Numerics is the numerical foundation of the AHSEsim initiative, aiming to provide methods and algorithms for numerical computations in science, engineering and every day use. Covered topics include special functions, linear algebra, probability models, random numbers, statistics, interpolation, integration, regression, curve fitting, integral transforms (FFT) and more.

In addition to the core .NET package (which is written entirely in C#), Numerics specifically supports F# with idiomatic extension modules and maintains mathematical data structures like BigRational that originated in the F# PowerPack. If a performance boost is needed, the managed-code provider backing its linear algebra routines and decompositions can be exchanged with wrappers for optimized native implementations such as Intel MKL.

AHSEsim Numerics is covered under the terms of the [MIT license](LICENSE.md). You may therefore link to it and use it in both opensource and proprietary software projects. We accept contributions!

### Current Version

![AHSEsim Numerics Version](https://buildstats.info/nuget/AHSEsim.Numerics) AHSEsim Numerics

![MKL Native Provider Version](https://buildstats.info/nuget/AHSEsim.Numerics.MKL.Win_x64) MKL Native Provider

![OpenBLAS Native Provider Version](https://buildstats.info/nuget/AHSEsim.Numerics.OpenBLAS.Win_x64) OpenBLAS Native Provider


Installation Instructions
-------------------------

The recommended way to get AHSEsim Numerics is to use NuGet. The following packages are provided and maintained in the public [NuGet Gallery](https://nuget.org/profiles/mathnet/).

Core Package:

- **AHSEsim.Numerics**
- **AHSEsim.Numerics.FSharp** - optional extensions for a better F# experience. BigRational.

Intel MKL Provider (optional):

- **AHSEsim.Numerics.Providers.MKL** - Binding to Native Intel MKL provider.
- **AHSEsim.Numerics.MKL.Win** - Native Intel MKL provider (Windows).
- **AHSEsim.Numerics.MKL.Win-x86** - Native Intel MKL provider (Windows/32-bit only).
- **AHSEsim.Numerics.MKL.Win-x64** - Native Intel MKL provider (Windows/64-bit only).

Data/IO Packages for reading and writing data (optional):

- **AHSEsim.Numerics.Data.Text** - Text-based matrix formats like CSV and MatrixMarket.
- **AHSEsim.Numerics.Data.Matlab** - MATLAB Level-5 matrix file format.

Platform Support and Dependencies
---------------------------------

Supported Platforms:

- .NET 10.0
- .NET Framework 4.8
- .NET Standard 2.0

Building AHSEsim Numerics
-------------------------

Windows (.NET): [![AppVeyor build status](https://ci.appveyor.com/api/projects/status/79j22c061saisces/branch/master)](https://ci.appveyor.com/project/cdrnet/mathnet-numerics)

You can build AHSEsim Numerics with an IDE like VisualStudio or JetBrains Rider, with MsBuild, .NET CLI tools or with FAKE (recommended).

FAKE:

    ./build.sh build (or build.cmd)
    ./build.sh test

.NET CLI:

    ./restore.sh (or restore.cmd)
    dotnet build AHSEsim.Numerics.sln

MsBuild/XBuild:

    ./restore.sh (or restore.cmd)
    msbuild AHSEsim.Numerics.sln

See [Build &amp; Tools](https://numerics.mathdotnet.com/Build.html) for full details
on how to build, generate documentation or even create a full release.
