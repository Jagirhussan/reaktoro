// Reaktor is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <memory>
#include <string>

// Reaktor includes
#include <Reaktor/Common/ChemicalScalar.hpp>
#include <Reaktor/Common/ChemicalVector.hpp>
#include <Reaktor/Common/ThermoVector.hpp>
#include <Reaktor/Core/Element.hpp>
#include <Reaktor/Core/Species.hpp>

namespace Reaktor {

/// A type used to define a phase and its attributes.
/// @see ChemicalSystem, Element, Species
/// @ingroup Core
class Phase
{
public:
    /// Construct a default Phase instance
    Phase();

    /// Set the name of the phase.
    auto setName(std::string name) -> void;

    /// Set the species of the phase.
    auto setSpecies(const std::vector<Species>& species) -> void;

    /// Set the function for the concentrations of the species in the phase.
    auto setConcentractionFunction(const ChemicalVectorFunction& function) -> void;

    /// Set the function for the natural log of the activity coefficients of the species in the phase.
    auto setActivityCoefficientFunction(const ChemicalVectorFunction& function) -> void;

    /// Set the function for the natural log of the activities of the species in the phase.
    auto setActivityFunction(const ChemicalVectorFunction& function) -> void;

    /// Set the function for the molar volume of the phase (in units of m3/mol).
    /// If the molar volume function of the phase is not set, then a default function
    /// based on the standard molar volumes of the species will be used:
    /// @f[
    ///       v_{\pi}=\sum_{i}x_{i}v_{i}^{\circ},
    /// @f]
    /// where @f$v_{\pi}@f$ is the molar volume of the phase; @f$x_{i}@f$ and
    /// @f$v_{i}@f$ are the molar fraction and standard molar volume of the *i*-th species.
    auto setMolarVolumeFunction(const ChemicalScalarFunction& function) -> void;

    /// Get the number of elements in the phase
    auto numElements() const -> unsigned;

    /// Get the number of species in the phase
    auto numSpecies() const -> unsigned;

    /// Get the name of the phase
    auto name() const -> const std::string&;

    /// Get the elements of the phase
    auto elements() const -> const std::vector<Element>&;

    /// Get the species of the phase
    auto species() const -> const std::vector<Species>&;

    /// Get the species of the phase with a given index
    /// @param index The index of the species
    auto species(Index index) const -> const Species&;

    /// Calculate the apparent standard molar Gibbs free energies of the species (in units of J/mol).
    auto standardGibbsEnergies(double T, double P) const -> ThermoVector;

    /// Calculate the apparent standard molar enthalpies of the species (in units of J/mol).
    auto standardEnthalpies(double T, double P) const -> ThermoVector;

    /// Calculate the apparent standard molar Helmholtz free energies of the species (in units of J/mol).
    auto standardHelmholtzEnergies(double T, double P) const -> ThermoVector;

    /// Calculate the standard molar entropies of the species (in units of J/K).
    auto standardEntropies(double T, double P) const -> ThermoVector;

    /// Calculate the standard molar volumes of the species (in units of m3/mol).
    auto standardVolumes(double T, double P) const -> ThermoVector;

    /// Calculate the apparent standard molar internal energies of the species (in units of J/mol).
    auto standardInternalEnergies(double T, double P) const -> ThermoVector;

    /// Calculate the standard molar isobaric heat capacity of the species (in units of J/(mol*K)).
    auto standardHeatCapacities(double T, double P) const -> ThermoVector;

    /// Calculate the concentrations of the species (no uniform units).
    auto concentrations(double T, double P, const Vector& n) const -> ChemicalVector;

    /// Calculate the natural log of the activity coefficients of the species.
    auto activityCoefficients(double T, double P, const Vector& n) const -> ChemicalVector;

    /// Calculate the natural log of the activities of the species.
    auto activities(double T, double P, const Vector& n) const -> ChemicalVector;

    /// Calculate the chemical potentials of the species (in units of J/mol).
    auto chemicalPotentials(double T, double P, const Vector& n) const -> ChemicalVector;

    /// Calculate the molar volume of the phase (in units of m3/mol).
    auto molarVolume(double T, double P, const Vector& n) const -> ChemicalScalar;

private:
    struct Impl;

    std::shared_ptr<Impl> pimpl;
};

/// Compare two Phase instances for less than
auto operator<(const Phase& lhs, const Phase& rhs) -> bool;

/// Compare two Phase instances for equality
auto operator==(const Phase& lhs, const Phase& rhs) -> bool;

/// Return a list of species (in order of appearance) in a list of phases
auto collectSpecies(const std::vector<Phase>& phases) -> std::vector<Species>;

} // namespace Reaktor
