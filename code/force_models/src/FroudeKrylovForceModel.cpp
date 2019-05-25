/*
 * FroudeKrylovForceModel.cpp
 *
 *  Created on: Oct 2, 2014
 *      Author: cady
 */

#include "FroudeKrylovForceModel.hpp"
#include "Body.hpp"
#include "SurfaceElevationInterface.hpp"

std::string FroudeKrylovForceModel::model_name() {return "non-linear Froude-Krylov";}

FroudeKrylovForceModel::FroudeKrylovForceModel(const std::string& body_name_, const EnvironmentAndFrames& env_) : ImmersedSurfaceForceModel(model_name(), body_name_, env_)
{
    if (env.w.use_count()==0)
    {
        THROW(__PRETTY_FUNCTION__, InvalidInputException, "Force model '" << model_name() << "' needs a wave model, even if it's 'no waves'");
    }
}

SurfaceForceModel::DF FroudeKrylovForceModel::dF(const FacetIterator& that_facet, const EnvironmentAndFrames& env, const BodyStates& states, const double t) const
{
    const EPoint dS = that_facet->area*that_facet->unit_normal;
    const ssc::kinematics::Point C(states.M->get_frame(), that_facet->centre_of_gravity);
    double eta = 0;
    for (auto it = that_facet->vertex_index.begin() ; it != that_facet->vertex_index.end() ; ++it)
    {
        eta += states.intersector->all_absolute_wave_elevations.at(*it);
    }
    if (not(that_facet->vertex_index.empty())) eta /= (double)that_facet->vertex_index.size();
    const double pdyn = env.w->get_dynamic_pressure(env.rho,env.g,C,env.k,eta,t);
    return DF(-pdyn*dS,C.v);
}

double FroudeKrylovForceModel::pe(const BodyStates& , const std::vector<double>& , const EnvironmentAndFrames& ) const
{
    return 0;
}
