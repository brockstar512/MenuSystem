// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup()
{
    AddToViewport();
    SetVisibility(ESlateVisibility::Visible);
    bIsFocusable = true;

    UWorld* World = GetWorld();
    if(World)
    {
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if(PlayerController)
        {
            FInputModeUIOnly InputModeData;
            InputModeData.SetWidgetToFocus(TakeWidget());
            InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputModeData);
            PlayerController->SetShowMouseCursor(true);


        }
    }
    UGameInstance* GameInstance = GetGameInstance();
    if(GameInstance)
    {
       MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
        
    }
   
}

bool UMenu::Initialize()
{
    if(!Super::Initialize())
    {
        return false;
    }
    //bind buttons
    if(HostButton)
    {
        HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
    }
    if(JoinButton)
    {
        JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
    }

    return true;
}

void UMenu::HostButtonClicked()
{
    if(GEngine){
        GEngine->AddOnScreenDebugMessage(
            -1,
            15.f,
            FColor::Yellow,
            FString(TEXT("Host Button Clicked"))
        );
    }
     if(MultiplayerSessionsSubsystem)
    {
        MultiplayerSessionsSubsystem->CreateSession(4,FString("FreeForeAll"));
        UWorld* World = GetWorld();
        if(World)
        {
            //if we are creating the session and are traveling then we are the listen server
            //we are going to add the listen option so we can wait for others
            World->ServerTravel("/Game/ThirdPersonCPP?Maps?Lobby?listen");
        }

    }
}

void UMenu::JoinButtonClicked()
{
        if(GEngine){
        GEngine->AddOnScreenDebugMessage(
            -1,
            15.f,
            FColor::Yellow,
            FString(TEXT("Join Button Clicked"))
        );
    }

}

