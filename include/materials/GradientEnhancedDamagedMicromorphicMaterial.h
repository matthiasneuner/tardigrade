#pragma once

#include <array>
#include "Material.h"
#include "MooseException.h"
#include<balance_equations.h>
#include<micromorphic_material_library.h>

//Forward declarations
class GradientEnhancedDamagedMicromorphicMaterial;
class Function;

using Arr3 = std::array< Real, 3 >;
using Arr33 = std::array< Arr3, 3 >;
using Arr333 = std::array< Arr33, 3 >;
using Arr3333 = std::array< Arr333, 3 >;

template <>
InputParameters validParams<GradientEnhancedDamagedMicromorphicMaterial>();

class GradientEnhancedDamagedMicromorphicMaterial : public Material{
    /*!
    ==============================
    |    GradientEnhancedDamagedMicromorphicMaterial    |
    ==============================

    Translation of the micromorphic_linear_elasticity library 
    available in the micromorphic_element repository for use 
    in MOOSE. More complete details of this model can be found 
    there.

    */

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        GradientEnhancedDamagedMicromorphicMaterial(const InputParameters &parameters);

    protected:
        virtual void initQpStatefulProperties() override;
        virtual void computeQpProperties() override;

    private:

        //Parameters
        std::vector<Real> _fparams;
        int               _n_ADD_DOF;
        int               _n_ADD_TERMS;
        int               _n_ADD_JACOBIANS;
        int               _n_SDVS;
        std::string       _model_name;
        bool              _MMS;

        const std::vector< const VariableGradient * > _grad_disp;
        const std::vector< const VariableGradient * > _grad_disp_old;

        const std::vector< const VariableValue * > _micro_disp_gradient;
        const std::vector< const VariableValue * > _micro_disp_gradient_old;

        const std::vector< const VariableGradient * > _grad_micro_disp_gradient;
        const std::vector< const VariableGradient * > _grad_micro_disp_gradient_old;

        const VariableValue & _k;

        MaterialProperty< Real > & _k_local;

        MaterialProperty< Arr33 > & _dk_local_dF;
        /* MaterialProperty< Arr3 > & _dk_local_dw; */
        /* MaterialProperty< Arr33 > & _dk_local_dgrad_w; */
        /* MaterialProperty< Real > & _dk_local_dk; */

        MaterialProperty< Real > & _nonlocal_radius;

        std::vector<Real>                           _ge_damage_parameters;
        MaterialProperty< std::vector< double > > & _ge_damage_statevars;
        const MaterialProperty< std::vector< double > > & _ge_damage_statevars_old;


        //Fundamental deformation measures
        MaterialProperty<std::vector<double>> & _deformation_gradient;
        MaterialProperty<std::vector<double>> & _micro_deformation;
        MaterialProperty<std::vector<std::vector<double>>> & _gradient_micro_displacement;

        //Stresses (Material Properties in MOOSE parlance)
        MaterialProperty<std::vector<double>>               & _cauchy;
        MaterialProperty<std::vector<double>>               & _s;
        MaterialProperty<std::vector<double>>               & _m;

        MaterialProperty<std::vector<double>>               & _PK2;
        MaterialProperty<std::vector<double>>               & _SIGMA;
        MaterialProperty<std::vector<double>>               & _M;

        MaterialProperty<std::vector<std::vector<double>>>  & _DPK2Dgrad_u;
        MaterialProperty<std::vector<std::vector<double>>>  & _DPK2Dphi;
        MaterialProperty<std::vector<std::vector<double>>>  & _DPK2Dgrad_phi;

        MaterialProperty<std::vector<std::vector<double>>>  & _DSIGMADgrad_u;
        MaterialProperty<std::vector<std::vector<double>>>  & _DSIGMADphi;
        MaterialProperty<std::vector<std::vector<double>>>  & _DSIGMADgrad_phi;

        MaterialProperty<std::vector<std::vector<double>>>  & _DMDgrad_u;
        MaterialProperty<std::vector<std::vector<double>>>  & _DMDphi;
        MaterialProperty<std::vector<std::vector<double>>>  & _DMDgrad_phi;

        //State variables
        MaterialProperty< std::vector< double > > & _SDVS;
        const MaterialProperty< std::vector< double > > & _old_SDVS;

        //TODO: Add additional values
        MaterialProperty<std::vector<std::vector<double>>>  & _ADD_TERMS;
        MaterialProperty<std::vector<std::vector<std::vector<double>>>>  & _ADD_JACOBIANS;

        //MMS function values
        const Function & _u1_fxn;
        const Function & _u2_fxn;
        const Function & _u3_fxn;
        const Function & _phi_11_fxn;
        const Function & _phi_22_fxn;
        const Function & _phi_33_fxn;
        const Function & _phi_23_fxn;
        const Function & _phi_13_fxn;
        const Function & _phi_12_fxn;
        const Function & _phi_32_fxn;
        const Function & _phi_31_fxn;
        const Function & _phi_21_fxn;

        //MMS stress measures
        MaterialProperty<std::vector<double>> & _PK2_MMS;
        MaterialProperty<std::vector<double>> & _SIGMA_MMS;
        MaterialProperty<std::vector<double>> & _M_MMS;
        MaterialProperty<std::vector<std::vector<double>>> & _ADD_TERMS_MMS;
};
