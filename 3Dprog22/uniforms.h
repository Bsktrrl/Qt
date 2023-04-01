#ifndef UNIFORMS_H
#define UNIFORMS_H

#include <QOpenGLFunctions_4_1_Core>

class Uniforms
{
public:
    Uniforms(GLint model, GLint view, GLint projection)
        :mMmatrixUniform(model), mVmatrixUniform(view), mPmatrixUniform(projection)
    {

    }

    Uniforms(GLint model, GLint view, GLint projection, GLint texture)
        :mMmatrixUniform(model), mVmatrixUniform(view), mPmatrixUniform(projection), mTextureSampler(texture)
    {

    }

    GLint mMmatrixUniform;
    GLint mVmatrixUniform;
    GLint mPmatrixUniform;
    GLint mTextureSampler;

    GLint mObjectColor;
    GLint mLightColor;
    GLint mViewPosition;
    GLint mLightPosition;
    GLint mAmbientUniform;
    GLint mDiffuseUniform;
    GLint mSpecularUniform;
    GLint mShininessUniform;
};

#endif // UNIFORMS_H
