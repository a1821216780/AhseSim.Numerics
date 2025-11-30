// <copyright file="RandomSerializationTests.cs" company="AHSEsim">
// AHSEsim Numerics, part of the AHSEsim Project
// http://numerics.mathdotnet.com
// http://github.com/mathnet/mathnet-numerics
//
// Copyright (c) 2009-2017 AHSEsim
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


// Rationale: System.Random is no longer serializable in .NET Core

using System;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using AHSEsim.Numerics.Random;
using NUnit.Framework;

namespace AHSEsim.Numerics.Tests.Random
{
    [TestFixture]
    public class RandomSerializationTests
    {
        [Test]
        [TestCase(typeof(MersenneTwister))]
        [TestCase(typeof(Mcg59))]
        [TestCase(typeof(Mcg31m1))]
        [TestCase(typeof(Mrg32k3a))]
        [TestCase(typeof(Palf))]
        [TestCase(typeof(WH1982))]
        [TestCase(typeof(WH2006))]
        [TestCase(typeof(Xorshift))]
        [TestCase(typeof(SystemRandomSource))]
        public void DataContractSerializationTest(Type randomType)
        {
            var expected = (RandomSource)Activator.CreateInstance(randomType);
            expected.NextDouble();
            expected.NextBoolean();

            var serializer = new DataContractSerializer(randomType);
            var stream = new MemoryStream();
            serializer.WriteObject(stream, expected);

            stream.Position = 0;
            var actual = (RandomSource)serializer.ReadObject(stream);

            Assert.That(actual.GetType(), Is.EqualTo(randomType));
            Assert.That(actual.NextDoubleSequence().Take(10).ToArray(), Is.EqualTo(expected.NextDoubleSequence().Take(10).ToArray()).AsCollection);
        }

        [Test]
        [TestCase(typeof(MersenneTwister))]
        [TestCase(typeof(Mcg59))]
        [TestCase(typeof(Mcg31m1))]
        [TestCase(typeof(Mrg32k3a))]
        [TestCase(typeof(Palf))]
        [TestCase(typeof(WH1982))]
        [TestCase(typeof(WH2006))]
        [TestCase(typeof(Xorshift))]
        [TestCase(typeof(SystemRandomSource))]
        public void BinaryFormatterSerializationTest(Type randomType)
        {
            var expected = (RandomSource)Activator.CreateInstance(randomType);
            expected.NextDouble();
            expected.NextBoolean();

#pragma warning disable SYSLIB0011 // 类型或成员已过时
            var serializer = new BinaryFormatter();
#pragma warning restore SYSLIB0011 // 类型或成员已过时
            var stream = new MemoryStream();
            serializer.Serialize(stream, expected);

            stream.Position = 0;
            var actual = (RandomSource)serializer.Deserialize(stream);

            Assert.That(actual.GetType(), Is.EqualTo(randomType));
            Assert.That(actual.NextDoubleSequence().Take(10).ToArray(), Is.EqualTo(expected.NextDoubleSequence().Take(10).ToArray()).AsCollection);
        }
    }
}


