// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintCallable)
		void MenuSetup();

		protected:
		virtual bool Initialize() override;

	private:
		UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;//name of the variable must have the same name as the widget in blueprints
		UPROPERTY(meta = (BindWidget))
		UButton* JoinButton;
	
		//because we are bding this function to an onclick event or delegate these have to be u functions
		UFUNCTION()
		void HostButtonClicked();
		UFUNCTION()
		void JoinButtonClicked();

		//subsystem designed to handle all online session functionality
		class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

};
