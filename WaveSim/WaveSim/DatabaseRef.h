#pragma once

#include <memory>
#include <unordered_map>

#include <Module.h>
#include <ShapesModule.h>
#include <SolverModule.h>

using namespace std;

class DatabaseRef final
{
public:

	const static int SHAPES_KEY = 0;	/*! The key for the module containing shapes. */
	const static int SOLVER_KEY = 1;	/*! The key for the module containing the WaveSolver. */

	/**
	*	Deconstructor.
	*
	*	This class uses the default decontructor as all memory is managed by smart pointers.
	*/
	~DatabaseRef() = default;

	/**
	*	Accessor method for the singleton class.
	*
	*	@return A static reference to the DatabaseRef.
	*/
	inline static DatabaseRef& GetInstance()
	{
		static DatabaseRef instance;
		return instance;
	}

	/**
	*	Accessor for modules.
	*
	*	Grabs a module from the hash table.
	*
	*	@param key The key for the module.
	*
	*	@return A module relative to the given key.
	*/
	inline shared_ptr<Module> GetModule(const int key) const
	{
		return mModules.at(key);
	}

private:

	/**
	 *	Constructor for the singleton class that holds multplie data modules.
	*/
	DatabaseRef()
		: mModules(unordered_map<int, shared_ptr<Module>>())
	{
		mModules[DatabaseRef::SHAPES_KEY] = dynamic_pointer_cast<Module>(make_shared<ShapesModule>());
		mModules[DatabaseRef::SOLVER_KEY] = dynamic_pointer_cast<Module>(make_shared<SolverModule>());
	}

	unordered_map<int, shared_ptr<Module>> mModules;	/*! A hashmap containing all the modules */
};
