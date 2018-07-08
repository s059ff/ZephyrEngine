#pragma once

#include "zephyr.linalg\Quaternion.h"

#include "common.h"
#include "Vector3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        value class Matrix3x3;

        /// <summary>
        /// �C�ӂ̎�����̉�]��\���܂��B
        /// </summary>
        public value class Quaternion
        {
        public:

            /// <summary>
            /// �C�ӂ̎�����̉�]��\���N�H�[�^�j�I�����쐬���܂��B
            /// </summary>
            /// <param name="axis">��]���B</param> 
            /// <param name="theta">��]�ʁB���W�A���Ŏw��B</param> 
            Quaternion(Vector3 axis, float theta)
            {
                zephyr::linalg::Vector3 _a(axis.Native);
                zephyr::linalg::Quaternion _q(_a, theta);
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this) = _q;
            }

            /// <summary>
            /// ��]�s����N�H�[�^�j�I���ɕϊ����܂��B
            /// </summary>
            /// <param name="matrix">��]�s��B</param> 
            Quaternion(Matrix3x3 matrix);

            /// <summary>
            /// �O������̓_���N�H�[�^�j�I���Ɋg�����܂��B
            /// </summary>
            /// <param name="point">�O������̓_�B</param> 
            Quaternion(Vector3 point)
            {
                zephyr::linalg::Vector3 _p(point.Native);
                zephyr::linalg::Quaternion _q(_p);
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this) = _q;
            }

            /// <summary>
            /// �P���ϊ���\���N�H�[�^�j�I���ɂ��ĕԂ��܂��B
            /// </summary>
            Quaternion Identity()
            {
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this).identity();
                return *this;
            }

            /// <summary>
            /// �N�H�[�^�j�I���𐳋K�����ĕԂ��܂��B
            /// </summary>
            Quaternion Normalize()
            {
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this).normalize();
                return *this;
            }

            /// <summary>
            /// �N�H�[�^�j�I���̓��ς�Ԃ��܂��B
            /// </summary>
            /// <param name="q1">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            /// <param name="q2">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            static float Inner(Quaternion q1, Quaternion q2)
            {
                auto& _q1 = reinterpret_cast<zephyr::linalg::Quaternion&>(q1);
                auto& _q2 = reinterpret_cast<zephyr::linalg::Quaternion&>(q2);

                return zephyr::linalg::inner(_q1, _q2);
            }

            /// <summary>
            /// ��̃N�H�[�^�j�I�����Ԃ���N�H�[�^�j�I����Ԃ��܂��B
            /// </summary>
            /// <param name="q0">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            /// <param name="q1">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            /// <param name="t">q0 ���� q1 �ɋ߂Â��銄���B</param> 
            static Quaternion Slerp(Quaternion q0, Quaternion q1, float t)
            {
                auto& _q0 = reinterpret_cast<zephyr::linalg::Quaternion&>(q0);
                auto& _q1 = reinterpret_cast<zephyr::linalg::Quaternion&>(q1);
                auto& _q2 = zephyr::linalg::slerp(_q0, _q1, t);

                return reinterpret_cast<Quaternion&>(_q2);
            }

            /// <summary>
            /// �N�H�[�^�j�I���ׂ̂�����v�Z���܂��B
            /// </summary>
            /// <param name="q">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            /// <param name="t">��]�̊����B t = 0 �̂Ƃ��A�P���N�H�[�^�j�I���A t = 1 �̂Ƃ��A���Ƃ̃N�H�[�^�j�I���Ɠ����B</param> 
            static Quaternion Pow(Quaternion q, float t)
            {
                auto& _q = reinterpret_cast<zephyr::linalg::Quaternion&>(q);
                auto& _q2 = zephyr::linalg::pow(_q, t);

                return reinterpret_cast<Quaternion&>(_q2);
            }

            /// <summary>
            /// �N�H�[�^�j�I���̋������v�Z���܂��B
            /// </summary>
            /// <param name="q">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            static Quaternion operator -(Quaternion q)
            {
                auto _q = -reinterpret_cast<zephyr::linalg::Quaternion&>(q);
                return reinterpret_cast<Quaternion&>(_q);
            }

            /// <summary>
            /// �N�H�[�^�j�I���̊O�ς��v�Z���܂��B
            /// </summary>
            /// <param name="q1">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            /// <param name="q2">���Z�Ώۂ̃N�H�[�^�j�I���B</param> 
            static Quaternion operator *(Quaternion q1, Quaternion q2)
            {
                auto& _q1 = reinterpret_cast<zephyr::linalg::Quaternion&>(q1);
                auto& _q2 = reinterpret_cast<zephyr::linalg::Quaternion&>(q2);
                auto& _q3 = zephyr::linalg::mul(_q1, _q2);

                return reinterpret_cast<Quaternion&>(_q3);
            }

            /// <summary>
            /// ���̃N�H�[�^�j�I�����\����]�̉�]�����擾���܂��B
            /// </summary>
            property Vector3 Axis { Vector3 get() { return reinterpret_cast<Vector3&>(reinterpret_cast<zephyr::linalg::Quaternion&>(*this).axis); }}

            /// <summary>
            /// ���̃N�H�[�^�j�I�����\����]�̉�]�p���擾���܂��B
            /// </summary>
            property float Theta { float get() { return reinterpret_cast<zephyr::linalg::Quaternion&>(*this).theta; }}

        public:

            float X, Y, Z, W;
        };
    }
}
