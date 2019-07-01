// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParser.h"


// Sets default values
AJsonParser::AJsonParser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJsonParser::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 1; i++)
	{
		LoadJson();
	}
}

void AJsonParser::LoadJson()
{
	const FString JsonFilePath = FPaths::ProjectContentDir() + "/JsonFiles/AnneCarwell2.json";
	FString JsonString; //Json converted to FString;

	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);//Load content of the json into JsonString

	//Create a json object to store the information from the json string
	//The json reader is used to deserialize the json object later on
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> GlobalVariables = JsonObject->GetArrayField("GlobalVariables");

		for (int globalZones = 0; globalZones != GlobalVariables.Num(); globalZones++)
		{
			TSharedPtr<FJsonObject> temp = GlobalVariables[globalZones]->AsObject();

			TArray<TSharedPtr<FJsonValue>> variables = temp->GetArrayField("Variables");


			//Generate Hints
			for (int variablesZones = 0; variablesZones != variables.Num(); variablesZones++)
			{
				TSharedPtr<FJsonObject> tempVariables = variables[variablesZones]->AsObject();

				FString Name = tempVariables->GetStringField("Variable");
				bool BoolValue = tempVariables->GetBoolField("Value");
				FString DescriptionValue = tempVariables->GetStringField("Description");

				FHintsBox tempJsonBox;

				tempJsonBox.hintName = Name;
				tempJsonBox.hintFind = BoolValue;
				tempJsonBox.description = DescriptionValue;

				Variables.Add(tempJsonBox);

				GLog->Log(tempJsonBox.hintName);
				//GLog->Log(tempJsonBox->hintFind);
				GLog->Log(tempJsonBox.description);

			}
		}
	}
}

// Called every frame
void AJsonParser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

