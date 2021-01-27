//----------------------------------------------------------------------------
//
//  TSDuck - The MPEG Transport Stream Toolkit
//  Copyright (c) 2005-2021, Thierry Lelegard
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//  THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------
//
//  Native implementation of the Java class io.tsduck.SectionFile.
//
//----------------------------------------------------------------------------

#include "tsSectionFile.h"
#include "tsDuckContext.h"
#include "tsjni.h"
TSDUCK_SOURCE;

#if !defined(TS_NO_JAVA)

// Method: io.tsduck.SectionFile.initNativeObject
// Signature: (Lio/tsduck/DuckContext;)V
TSDUCKJNI void JNICALL Java_io_tsduck_SectionFile_initNativeObject(JNIEnv* env, jobject obj, jobject jduck)
{
    // Make sure we do not allocate twice (and lose previous instance).
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    if (sf == nullptr) {
        ts::DuckContext* duck = nullptr;
        if (jduck != nullptr) {
            duck = ts::jni::GetPointerField<ts::DuckContext>(env, jduck, "nativeObject");
        }
        if (duck == nullptr) {
            // We must have a DuckContext with SectionFile. Create one with all default values.
            duck = new ts::DuckContext;
            // And save it in the Java SectionFile object to delete it later.
            ts::jni::SetPointerField(env, obj, "nativeDuckContext", duck);
        }
        ts::jni::SetPointerField(env, obj, "nativeObject", new ts::SectionFile(*duck));
    }
}

// Method: io.tsduck.SectionFile.delete
// Signature: ()V
TSDUCKJNI void JNICALL Java_io_tsduck_SectionFile_delete(JNIEnv* env, jobject obj)
{
    // Delete the SectionFile object.
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    if (sf != nullptr) {
        delete sf;
        ts::jni::SetLongField(env, obj, "nativeObject", 0);
    }
    // If one DuckContext was allocated in the constructor, delete it as well.
    ts::DuckContext* duck = ts::jni::GetPointerField<ts::DuckContext>(env, obj, "nativeDuckContext");
    if (duck != nullptr) {
        delete duck;
        ts::jni::SetLongField(env, obj, "nativeDuckContext", 0);
    }
}

// Method: io.tsduck.SectionFile.clear
// Signature: ()V
TSDUCKJNI void JNICALL Java_io_tsduck_SectionFile_clear(JNIEnv* env, jobject obj)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    if (sf != nullptr) {
        sf->clear();
    }
}

// Method: io.tsduck.SectionFile.binarySize
// Signature: ()I
TSDUCKJNI jint JNICALL Java_io_tsduck_SectionFile_binarySize(JNIEnv* env, jobject obj)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf == nullptr ? 0 : jint(sf->binarySize());
}

// Method: io.tsduck.SectionFile.sectionsCount
// Signature: ()I
TSDUCKJNI jint JNICALL Java_io_tsduck_SectionFile_sectionsCount(JNIEnv* env, jobject obj)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf == nullptr ? 0 : jint(sf->sectionsCount());
}

// Method: io.tsduck.SectionFile.tablesCount
// Signature: ()I
TSDUCKJNI jint JNICALL Java_io_tsduck_SectionFile_tablesCount(JNIEnv* env, jobject obj)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf == nullptr ? 0 : jint(sf->tablesCount());
}

// Method: io.tsduck.SectionFile.loadBinary
// Signature: (Ljava/lang/String;)Z
TSDUCKJNI jboolean JNICALL Java_io_tsduck_SectionFile_loadBinary(JNIEnv* env, jobject obj, jstring jname)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf != nullptr && sf->loadBinary(ts::jni::ToUString(env, jname));
}

// Method: io.tsduck.SectionFile.saveBinary
// Signature: (Ljava/lang/String;)Z
TSDUCKJNI jboolean JNICALL Java_io_tsduck_SectionFile_saveBinary(JNIEnv* env, jobject obj, jstring jname)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf != nullptr && sf->saveBinary(ts::jni::ToUString(env, jname));
}

// Method: io.tsduck.SectionFile.loadXML
// Signature: (Ljava/lang/String;)Z
TSDUCKJNI jboolean JNICALL Java_io_tsduck_SectionFile_loadXML(JNIEnv* env, jobject obj, jstring jname)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf != nullptr && sf->loadXML(ts::jni::ToUString(env, jname));
}

// Method: io.tsduck.SectionFile.saveXML
// Signature: (Ljava/lang/String;)Z
TSDUCKJNI jboolean JNICALL Java_io_tsduck_SectionFile_saveXML(JNIEnv* env, jobject obj, jstring jname)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf != nullptr && sf->saveXML(ts::jni::ToUString(env, jname));
}

// Method: io.tsduck.SectionFile.saveJSON
// Signature: (Ljava/lang/String;)Z
TSDUCKJNI jboolean JNICALL Java_io_tsduck_SectionFile_saveJSON(JNIEnv* env, jobject obj, jstring jname)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return sf != nullptr && sf->saveJSON(ts::jni::ToUString(env, jname));
}

// Method: io.tsduck.SectionFile.toXML
// Signature: ()Ljava/lang/String;
TSDUCKJNI jstring JNICALL Java_io_tsduck_SectionFile_toXML(JNIEnv* env, jobject obj)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return ts::jni::ToJString(env, sf != nullptr ? sf->toXML() : ts::UString());
}

// Method: io.tsduck.SectionFile.toJSON
// Signature: ()Ljava/lang/String;
TSDUCKJNI jstring JNICALL Java_io_tsduck_SectionFile_toJSON(JNIEnv* env, jobject obj)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    return ts::jni::ToJString(env, sf != nullptr ? sf->toJSON() : ts::UString());
}


// Method: io.tsduck.SectionFile.fromBinary
// Signature: ([B)Z
TSDUCKJNI jboolean JNICALL Java_io_tsduck_SectionFile_fromBinary(JNIEnv* env, jobject obj, jbyteArray jdata)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    if (sf == nullptr) {
        return false;
    }
    else {
        void* data = env->GetPrimitiveArrayCritical(jdata, nullptr);
        const bool result = sf->loadBuffer(data, size_t(env->GetArrayLength(jdata)));
        env->ReleasePrimitiveArrayCritical(jdata, data, JNI_ABORT);
        return result;
    }
}

// Method: io.tsduck.SectionFile.fromBinary
// Signature: ()[B)Z
TSDUCKJNI jbyteArray JNICALL Java_io_tsduck_SectionFile_toBinary(JNIEnv* env, jobject obj)
{
    ts::SectionFile* sf = ts::jni::GetPointerField<ts::SectionFile>(env, obj, "nativeObject");
    if (sf == nullptr) {
        return nullptr;
    }
    else {
        const size_t size = sf->binarySize();
        const jbyteArray result = env->NewByteArray(size);
        void* data = env->GetPrimitiveArrayCritical(result, nullptr);
        sf->saveBuffer(data, size);
        env->ReleasePrimitiveArrayCritical(result, data, 0);
        return result;
    }
}

#endif // TS_NO_JAVA
