#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	sceneSetup();
}


PhysicsEngine* PhysicsEngine::getInstance()
{
    static PhysicsEngine physics;
    return &physics;
}


void PhysicsEngine::losing()
{
	int one = w1->getMotorTorque();
	int two = w2->getMotorTorque();
	int three = w3->getMotorTorque();
	int four = w4->getMotorTorque();
	if (one > 0 && two > 0 && three > 0 && four > 0)
	{
		if (one > 10)
		{
			w1->setMotorTorque(one * 0.7);
			w2->setMotorTorque(two * 0.7);
			w3->setMotorTorque(three * 0.7);
			w4->setMotorTorque(four * 0.7);
		}
		else
		{
			w1->setMotorTorque(0);
			w2->setMotorTorque(0);
			w3->setMotorTorque(0);
			w4->setMotorTorque(0);
		}
	}
	else if (one < 0 && two < 0 && three < 0 && four < 0)
	{
		if (one < -10)
		{
			w1->setMotorTorque(one * 0.7);
			w2->setMotorTorque(two * 0.7);
			w3->setMotorTorque(three * 0.7);
			w4->setMotorTorque(four * 0.7);
		}
		else
		{
			w1->setMotorTorque(0);
			w2->setMotorTorque(0);
			w3->setMotorTorque(0);
			w4->setMotorTorque(0);
		}
	}
}

void PhysicsEngine::setupPlayScene(vector<Entity*>* cars)
{
    std::vector<Entity*>* tmpCars =  cars;
	physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	physicsSDK->setParameter(NX_SKIN_WIDTH, 0.01f);

    physicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
    physicsSDK->setParameter(NX_VISUALIZE_BODY_ANG_VELOCITY, 1);
    physicsSDK->setParameter(NX_VISUALIZE_BODY_LIN_VELOCITY, 1);
    physicsSDK->setParameter(NX_VISUALIZE_ACTIVE_VERTICES, 1);
    physicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
    physicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
    physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);


	NxSceneDesc sceneDesc;
	sceneDesc.simType = NX_SIMULATION_SW;
	NxVec3 defaultGravity(0,-9.8f*(10.0f),0);
	sceneDesc.gravity = defaultGravity;
	scene = physicsSDK->createScene(sceneDesc);

	//Create the default material
	NxMaterial* defaultMaterial = scene->getMaterialFromIndex(0);
	//defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);

	//groundPlane = createGroundPlane();
	//box = createBox();

    NxActor* box = createCarChassis();              //create a Chassis
    NxWheelShape* wheel =  AddWheelToActor(box, 1.0f,0,1.2) ;     //Create a wheel, and attach it to the Chassis
	NxWheelShape* wheel2 = AddWheelToActor(box, 1.0f,0,-1.2);
    NxWheelShape* wheel3 = AddWheelToActor(box, -1.0f,0,1.2);
	NxWheelShape* wheel4 = AddWheelToActor(box, -1.0f,0,-1.2);

    //NxWheelShape* wheel3 = AddWheelToActor(box, -0.5f,0.05);

    Entity* entityCar1 = new Entity();    
    //EntityComponent* ec_car = new EntityComponent();
    //ec_car->setActor(box);
    entityCar1->addDriveWheel(wheel);
	entityCar1->addDriveWheel(wheel2);
    entityCar1->addPassiveWheel(wheel3);
	entityCar1->addPassiveWheel(wheel4);
	w1 = wheel;
	w2 = wheel2;
	w3 = wheel3;
	w4 = wheel4;
    //Camera newCamera = Camera(box);
    entityCar1->aCam = new Camera(box);

   // entityCar1.components.push_back( &ec_car );
    //entityCar1->addComponent( ec_car );    
	entityCar1->setActor(box);
    tmpCars->at(0) = entityCar1;    
	box->setSleepEnergyThreshold(0);
}

void PhysicsEngine::sceneSetup()
{
	physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	physicsSDK->setParameter(NX_SKIN_WIDTH, 0.01f);

	NxSceneDesc sceneDesc;
	sceneDesc.simType = NX_SIMULATION_SW;
	NxVec3 defaultGravity(0,-9.8f*(10.0f),0);
	sceneDesc.gravity = defaultGravity;
	scene = physicsSDK->createScene(sceneDesc);

	//Create the default material
	NxMaterial* defaultMaterial = scene->getMaterialFromIndex(0);
	//defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);

	groundPlane = createGroundPlane();
	box = createBox(0,0,0);
}


void PhysicsEngine::step(float deltaTime)
{
	scene->simulate(deltaTime);
	scene->flushStream();
	scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
}


void PhysicsEngine::releaseNx() 
{
	if(scene)
	{
		while(!scene->fetchResults(NX_RIGID_BODY_FINISHED, false));
		physicsSDK->releaseScene(*scene);
	}
	if(physicsSDK) physicsSDK->release();
}


void PhysicsEngine::resetNx()
{
	releaseNx();
	sceneSetup();
}

//Needs deltaTime from gameClock in the Game class
//NxVec3 PhysicsEngine::ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength)
//{
//	NxVec3 forceVec = forceStrength*forceDir*deltaTime;
//	actor->addForce(forceVec);
//	return forceVec;
//}

//Needs deltaTime from gameClock in the Game class
//NxVec3 PhysicsEngine::ApplyForceToBox(const NxVec3& forceDir, const NxReal forceStrength)
//{
//	NxVec3 forceVec = forceStrength*forceDir*deltaTime;
//	box->addForce(forceVec);
//	return forceVec;
//}


NxActor* PhysicsEngine::createGroundPlane()
{
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	return scene->createActor(actorDesc);
}


NxActor* PhysicsEngine::createBox(float x, float y, float z) 
{
	//Set the box starting height
	NxVec3 position(x, y, z);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;

	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.5,0.5,0.5);
	//boxDesc.localPose.t = position;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;

	NxActor *actor = scene->createActor(actorDesc);
	actor->userData = (void*)size_t(0.5f);

	return actor;
}

NxActor* PhysicsEngine::createStaticBox(float x, float y, float z) 
{
	//Set the box starting height
	NxVec3 position(x, y, z);

	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.5,0.5,0.5);
	//boxDesc.localPose.t = position;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body = NULL;                  //Set as static
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;

	NxActor *actor = scene->createActor(actorDesc);
	actor->userData = (void*)size_t(0.5f);

	return actor;
}


/**
This Method doesn't work
**/
NxActor* PhysicsEngine::createTriMesh(float x, float y, float z, ObjModel aModel) 
{
	NxVec3 position(x, y, z);

    NxVec3* gVerts;
    NxVec3* gNormals;
    NxU32* gFaces;

    //aModel.getVerticies()->size();
    gVerts = new NxVec3 [aModel.getVerticies()->size()];


    for (int v = 0; v < aModel.getVerticies()->size(); v++)
    {
        gVerts[v] = ( NxVec3(aModel.getVerticies()->at(v).x, aModel.getVerticies()->at(v).y, aModel.getVerticies()->at(v).z) );
    }


   // aModel.getVerticies()->size();
    gFaces = new NxU32[(aModel.getFaces()->size()*3)+3];
    //for (int f = 0; f < aModel.getFaces()->size(); f++)
    //{
    //    gFaces[f]
    //}


    for (int v = 0; v < (aModel.getFaces()->size()); v=v+1)
    {
        gFaces[v*3] = ( NxU32(aModel.getFaces()->at(v).at(0).vertIndex) );
        gFaces[(v*3)+1] = ( NxU32(aModel.getFaces()->at(v).at(1).vertIndex) );
        gFaces[(v*3)+2] = ( NxU32(aModel.getFaces()->at(v).at(2).vertIndex) );
    }

    //aModel.getVertexNormals()->size();
    gNormals = new NxVec3[aModel.getVertexNormals()->size()];

    for (int n = 0; n < aModel.getVertexNormals()->size(); n++)
    {
        gNormals[n] = ( NxVec3(aModel.getVertexNormals()->at(n).x, aModel.getVertexNormals()->at(n).y, aModel.getVertexNormals()->at(n).z) );
    }

    printf("PHYSIC_MESH: Ver:%i, Tri:%i\n",aModel.getVerticies()->size(), aModel.getFaces()->size());

	// Build physical model
	NxTriangleMeshDesc triMeshDesc;
	triMeshDesc.numVertices					= aModel.getVerticies()->size();
	triMeshDesc.numTriangles				= aModel.getFaces()->size();
	triMeshDesc.pointStrideBytes			= sizeof(NxVec3);
	triMeshDesc.triangleStrideBytes			= 3*sizeof(NxU32);
	triMeshDesc.points						= gVerts;
	triMeshDesc.triangles					= gFaces;							
	triMeshDesc.flags						= 0;

	//add the mesh material data:
	//triMeshDesc.materialIndexStride			= sizeof(NxMaterialIndex);
	//triMeshDesc.materialIndices				= gTerrainMaterials;

	//triMeshDesc.heightFieldVerticalAxis		= NX_Y;
	//triMeshDesc.heightFieldVerticalExtent	= -1000.0f;

	NxTriangleMeshShapeDesc triMeshShapeDesc;

    NxInitCooking();

     MemoryWriteBuffer buf;
        NxCookingParams params;  
        params.targetPlatform = PLATFORM_PC;  
        params.skinWidth = 0.5f;  
        params.hintCollisionSpeed = false;  
        NxSetCookingParams(params);  
     bool status = NxCookTriangleMesh(triMeshDesc, buf); 

  	MemoryReadBuffer readBuffer(buf.data);


  	triMeshShapeDesc.meshData = physicsSDK->createTriangleMesh(readBuffer);
    ///triMeshShapeDesc.meshFlags = NxMeshFlags::NX_MF_FLIPNORMALS;        //seems to help??

	//
	// Please note about the created Triangle Mesh, user needs to release it when no one uses it to save memory. It can be detected
	// by API "meshData->getReferenceCount() == 0". And, the release API is "gPhysicsSDK->releaseTriangleMesh(*meshData);"
	//
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&triMeshShapeDesc);

    actorDesc.body = NULL;                  //Set as static
	actorDesc.density = 1000.0f;

    actorDesc.globalPose.t = position;
	NxActor *actor = scene->createActor(actorDesc);
	actor->userData = (void*)0;


     //actor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC,true);

	NxCloseCooking();
    return actor;

    //actor->setSleepEnergyThreshold(0);          //Testing
    //return scene->createActor(actorDesc);
}


NxActor* PhysicsEngine::createCarChassis() 
{
	//Set the box starting height
	NxVec3 position(0.0, 3.5, 0.0);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	//bodyDesc.angularDamping	= 0.5f;
	bodyDesc.angularDamping	= 20.0f;
	bodyDesc.linearDamping = 0.05f;


	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxShapes[2];
	boxShapes[0].dimensions.set(2.5f, 0.4f, 1.2f);
	boxShapes[1].dimensions.set(1.f, 0.3f, 1.1f);
	boxShapes[1].localPose.t.set(-0.3f, 0.7f, 0.f);

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxShapes[0]);
	actorDesc.shapes.pushBack(&boxShapes[1]);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;

	NxActor *actor = scene->createActor(actorDesc);
	actor->setCMassOffsetLocalPosition(NxVec3(0, -2.5, 0));

	return actor;
}

NxWheelShape* PhysicsEngine::AddWheelToActor(NxActor* actor, float x,float y, float z)
{
	NxWheelShapeDesc wheelShapeDesc;

	// Create a shared car wheel material to be used by all wheels
	if (!wsm)
	{
		NxMaterialDesc m;
		m.flags |= NX_MF_DISABLE_FRICTION;
		wsm = scene->createMaterial(m);
	}
	wheelShapeDesc.materialIndex = wsm->getMaterialIndex();


	wheelShapeDesc.localPose.t = NxVec3(x, y, z);//wheelDesc->position;

	NxQuat q;
	q.fromAngleAxis(90, NxVec3(0,1,0));
	wheelShapeDesc.localPose.M.fromQuat(q);

	NxReal heightModifier = 2.0f;  //??    //(wheelDesc->wheelSuspension + wheelDesc->wheelRadius) / wheelDesc->wheelSuspension;

	wheelShapeDesc.suspension.spring = 7000.0f * heightModifier;    //??     //wheelDesc->springRestitution*heightModifier;
	wheelShapeDesc.suspension.damper = 0 * heightModifier;  //wheelDesc->springDamping*heightModifier;
	wheelShapeDesc.suspension.targetValue = 0 * heightModifier;  //wheelDesc->springBias*heightModifier;

	wheelShapeDesc.radius = 0.5f;  //wheelDesc->wheelRadius;
	wheelShapeDesc.suspensionTravel =  0.5f; //wheelDesc->wheelSuspension; 
	wheelShapeDesc.inverseWheelMass = 0.1;	//not given!? TODO



    NxTireFunctionDesc latff;
    latff.asymptoteSlip = 2.0f;
    latff.asymptoteValue = 0.01f;
    latff.extremumSlip = 1.0f;
    latff.extremumValue = 0.02f;
    latff.stiffnessFactor = 1000000.0f;

    NxTireFunctionDesc lotff;
    lotff.asymptoteSlip = 2.0f;
    lotff.asymptoteValue = 0.01f;
    lotff.extremumSlip = 1.0f;
    lotff.extremumValue = 0.02f;
    lotff.stiffnessFactor = 1000000.0f;

    wheelShapeDesc.lateralTireForceFunction = latff;	//TODO
	wheelShapeDesc.longitudalTireForceFunction = lotff;	//TODO

    NxWheelShape* wheelShape;
	wheelShape = static_cast<NxWheelShape *>(actor->createShape(wheelShapeDesc));

    return wheelShape;
}

void PhysicsEngine::resetBox()
{
	box->setGlobalPosition(NxVec3(0,3.5,0));
	scene->flushCaches();
}

void PhysicsEngine::resetBoxHigh()
{
	box->setGlobalPosition(NxVec3(0,35.0f,0));
	scene->flushCaches();
}


NxScene* PhysicsEngine::getScene()
{
	return scene;
}


void PhysicsEngine::accel()
{
	//w1->setMotorTorque(2000);
	//w2->setMotorTorque(2000);
	//w3->setMotorTorque(1000);
	//w4->setMotorTorque(1000);
	//box->wakeUp();
}

void PhysicsEngine::rev()
{
	w1->setMotorTorque(-2000);
	w2->setMotorTorque(-2000);
	//w3->setMotorTorque(-1000);
	//w4->setMotorTorque(-1000);
	//box->wakeUp();
}

void PhysicsEngine::steer(int mag)
{
	//w1->setSteerAngle(-30);
    w1->setSteerAngle(mag);
    w2->setSteerAngle(mag);
    w3->setSteerAngle(mag);
    w4->setSteerAngle(mag);
}


// Work on getting braking done
// Make sure actor doesn't go to sleep (already done), but remeber to do it.
// Find a way to get this working through the entity class
